#ifndef NAIVE_DB_TABLE_H
#define NAIVE_DB_TABLE_H

#include <cstdint>

#include "Row.h"
#include "Pager.h"

class Table {
 public:

  uint8_t* slot(uint32_t row_num);

  uint32_t num_rows = 0;
  virtual ~Table();

  explicit Table(const std::string&);

 private :
  Pager pager_;
};

#endif  // NAIVE_DB_TABLE_H
