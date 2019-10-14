#ifndef NAIVE_DB_TABLE_H
#define NAIVE_DB_TABLE_H

#include <cstdint>

#include "Row.h"

class Table {
 public:
  enum : uint32_t {
    PAGE_SIZE = 4096,
    TABLE_MAX_PAGES = 100,
    ROWS_PER_PAGE = PAGE_SIZE / Row::ROW_SIZE,
    TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES,
  };

  uint8_t* slot(uint32_t row_num);

  uint32_t num_rows = 0;
  virtual ~Table();

  Table();

 private :
  uint8_t* pages_[TABLE_MAX_PAGES]{};
};

#endif  // NAIVE_DB_TABLE_H
