#include "Table.h"

uint8_t* Table::slot(uint32_t row_num) {
  uint32_t page_num = row_num / ROWS_PER_PAGE;
  uint8_t* page = pages_[page_num];
  if (page == nullptr) {
    // Allocate memory only when we try to access page
    page = pages_[page_num] = new uint8_t[PAGE_SIZE];
  }
  uint32_t row_offset = row_num % ROWS_PER_PAGE;
  uint32_t byte_offset = row_offset * Row::ROW_SIZE;
  return page + byte_offset;
}

Table::Table() {
  for (auto & page : pages_) {
    page = nullptr;
  }
}

Table::~Table() {
  for (auto & page : pages_) {
    delete page;
  }
}
