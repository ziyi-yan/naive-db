#include <sstream>
#include <string>

#include "absl/strings/match.h"

#include "Statement.h"

Statement::PrepareResult Statement::prepare(const std::string& line) {
  if (absl::StartsWithIgnoreCase(line, "insert")) {
    type_ = Statement::Type::Insert;
    int args_assigned = sscanf(
        line.c_str(), "insert %d %s %s", &row_to_insert_.id,
        row_to_insert_.username, row_to_insert_.email);
    if (args_assigned < 3) {
      return Statement::PrepareResult::SyntaxError;
    }
    return Statement::PrepareResult::Success;
  }
  if (absl::StartsWithIgnoreCase(line, "select")) {
    type_ = Statement::Type::Select;
    return Statement::PrepareResult::Success;
  }

  return Statement::PrepareResult::UnrecognizedStatement;
}
Statement::Type Statement::type() { return type_; }
