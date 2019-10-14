#ifndef NAIVE_DB_STATEMENT_H
#define NAIVE_DB_STATEMENT_H
#include <string>
#include "Row.h"
struct Statement {
 public:
  enum class PrepareResult {
    Success,
    UnrecognizedStatement,
    SyntaxError,
    StringTooLong,
    NegativeID,
  };
  enum class Type { Insert, Select };

  Type type();

  PrepareResult prepare(const std::string& line);

  Row* row_to_insert() { return &row_to_insert_; }

 private:
  Type type_;
  Row row_to_insert_;
};

#endif  // NAIVE_DB_STATEMENT_H
