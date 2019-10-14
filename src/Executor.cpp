#include "absl/strings/str_format.h"

#include "Executor.h"
#include "Table.h"

Executor::ExecuteResult Executor::execute(Statement st, Table* tbl) {
  switch (st.type()) {
    case (Statement::Type::Insert):
      return execute_insert(st, tbl);
    case (Statement::Type::Select):
      return execute_select(st, tbl);
  }
}
Executor::ExecuteResult Executor::execute_insert(Statement st, Table* tbl) {
  if (tbl->num_rows >= Table::TABLE_MAX_ROWS) {
    return ExecuteResult::TableFull;
  }

  auto row = st.row_to_insert();
  auto last_slot = tbl->slot(tbl->num_rows);
  row->serializeTo(last_slot);

  tbl->num_rows += 1;

  return ExecuteResult::Success;
}

Executor::ExecuteResult Executor::execute_select(Statement st, Table* tbl) {
  Row row{};
  for (uint32_t i = 0; i < tbl->num_rows; i++) {
    auto slot = tbl->slot(i);
    row.deserializeFrom(slot);
    printRow(row);
  }
  return ExecuteResult::Success;
}

void Executor::printRow(Row row) {
  absl::PrintF("%d\t%s\t%s\n", row.id, row.username, row.email);
}
