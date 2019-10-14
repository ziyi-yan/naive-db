#include "Table.h"

uint8_t* Table::slot(uint32_t row_num) {
  uint32_t page_num = row_num / Pager::ROWS_PER_PAGE;
  uint8_t* page = pager_.getPage(page_num);
  uint32_t row_offset = row_num % Pager::ROWS_PER_PAGE;
  uint32_t byte_offset = row_offset * Row::ROW_SIZE;
  return page + byte_offset;
}

Table::Table(const std::string& filename) : pager_{filename}{
  num_rows = pager_.file_length / Row::ROW_SIZE;
}

Table::~Table() {
  pager_.saveRows(num_rows);
}

