#ifndef NAIVE_DB_EXECUTOR_H
#define NAIVE_DB_EXECUTOR_H

#include "Statement.h"
#include "Table.h"
class Executor {
 public:
  enum class ExecuteResult { Success, TableFull };

  ExecuteResult execute(Statement st, Table* tbl);

 private:
  ExecuteResult execute_insert(Statement st, Table* tbl);
  ExecuteResult execute_select(Statement st, Table* tbl);
  void printRow(Row row);
  void printHeader();
};

#endif  // NAIVE_DB_EXECUTOR_H
