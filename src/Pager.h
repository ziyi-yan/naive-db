#ifndef NAIVE_DB_PAGER_H
#define NAIVE_DB_PAGER_H

#include <cstdint>
#include <string>

#include "Row.h"

class Pager {
 public:
  enum : uint32_t {
    PAGE_SIZE = 4096,
    TABLE_MAX_PAGES = 100,
    ROWS_PER_PAGE = PAGE_SIZE / Row::ROW_SIZE,
    TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES,
  };

  explicit Pager(const std::string& filename);
  uint32_t file_length;
  uint8_t* getPage(uint32_t page_num);
  void saveRows(uint32_t num_rows);

 private:
  int file_descriptor;
  uint8_t* pages_[Pager::TABLE_MAX_PAGES]{};
  uint32_t last_page_num = 0;
  void flush(uint32_t i, uint32_t size);
};

#endif  // NAIVE_DB_PAGER_H
