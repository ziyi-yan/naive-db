
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>

#include <absl/strings/str_format.h>

#include "Pager.h"

Pager::Pager(const std::string& filename) {
  int fd = open(filename.c_str(),
                O_RDWR |      // Read/Write mode
                    O_CREAT,  // Create file if it does not exist
                S_IWUSR |     // User write permission
                    S_IRUSR   // User read permission
  );

  if (fd == -1) {
    absl::PrintF("Unable to open file\n");
    exit(EXIT_FAILURE);
  }

  off_t length = lseek(fd, 0, SEEK_END);

  file_descriptor = fd;
  file_length = length;

  for (auto& page : pages_) {
    page = nullptr;
  }
}
uint8_t* Pager::getPage(uint32_t page_num) {
  if (page_num > Pager::TABLE_MAX_PAGES) {
    absl::PrintF("Tried to fetch page number out of bounds. %d > %d\n",
                 page_num, Pager::TABLE_MAX_PAGES);
    exit(EXIT_FAILURE);
  }

  if (pages_[page_num] == nullptr) {
    // Cache miss. Allocate memory and load from file.
    auto page = new uint8_t[Pager::PAGE_SIZE];
    uint32_t num_pages = file_length / Pager::PAGE_SIZE;

    // We might save a partial page at the end of the file
    if (file_length % Pager::PAGE_SIZE) {
      num_pages += 1;
    }

    if (page_num <= num_pages) {
      lseek(file_descriptor, page_num * Pager::PAGE_SIZE, SEEK_SET);
      ssize_t bytes_read = read(file_descriptor, page, Pager::PAGE_SIZE);
      if (bytes_read == -1) {
        absl::PrintF("Error reading file: %d\n", errno);
        exit(EXIT_FAILURE);
      }
    }

    pages_[page_num] = page;
  }

  return pages_[page_num];
}

void Pager::saveRows(uint32_t num_rows) {
  uint32_t num_full_pages = num_rows / ROWS_PER_PAGE;

  for (uint32_t i = 0; i < num_full_pages; i++) {
    if (pages_[i] == nullptr) {
      continue;
    }
    flush(i, Pager::PAGE_SIZE);
    delete pages_[i];
    pages_[i] = nullptr;
  }

  // There may be a partial page to write to the end of the file
  // This should not be needed after we switch to a B-tree
   uint32_t num_additional_rows = num_rows % ROWS_PER_PAGE;
  if (num_additional_rows > 0) {
    uint32_t page_num = num_full_pages;
    if (pages_[page_num] != nullptr) {
      flush(page_num, num_additional_rows * Row::ROW_SIZE);
      delete pages_[page_num];
      pages_[page_num] = nullptr;
    }
  }

  int result = close(file_descriptor);
  if (result == -1) {
    absl::PrintF("Error closing db file.\n");
    exit(EXIT_FAILURE);
  }
  for (auto& page : pages_) {
    if (page) {
      delete page;
      page = nullptr;
    }
  }
}

void Pager::flush(uint32_t page_num, uint32_t size) {
  if (pages_[page_num] == nullptr) {
    absl::PrintF("Tried to flush null page\n");
    exit(EXIT_FAILURE);
  }

  off_t offset = lseek(file_descriptor, page_num * Pager::PAGE_SIZE, SEEK_SET);

  if (offset == -1) {
    absl::PrintF("Error seeking: %d\n", errno);
    exit(EXIT_FAILURE);
  }

  ssize_t bytes_written = write(file_descriptor, pages_[page_num], size);

  if (bytes_written == -1) {
    absl::PrintF("Error writing: %d\n", errno);
    exit(EXIT_FAILURE);
  }
}
