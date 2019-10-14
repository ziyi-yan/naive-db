#include <string>

#include "absl/strings/match.h"

#include "Statement.h"

Statement::PrepareResult Statement::prepare(absl::string_view line) {
  if (absl::StartsWithIgnoreCase(line, "insert")) {
    type_ = Statement::Type::Insert;
    return Statement::PrepareResult::Success;
  }
  if (absl::StartsWithIgnoreCase(line, "select")) {
    type_ = Statement::Type::Insert;
    return Statement::PrepareResult::Success;
  }

  return Statement::PrepareResult::UnrecognizedStatement;
}
Statement::Type Statement::type() { return type_; }
