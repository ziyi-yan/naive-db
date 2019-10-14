#include <absl/strings/numbers.h>
#include <absl/strings/str_split.h>
#include <sstream>
#include <string>

#include "absl/strings/match.h"

#include "Statement.h"

Statement::PrepareResult Statement::prepare(const std::string& line) {
  if (absl::StartsWithIgnoreCase(line, "insert")) {
    type_ = Statement::Type::Insert;
    std::vector<absl::string_view> v =
        absl::StrSplit(line, ' ', absl::SkipWhitespace{});
    if (v.size() != 4) {
      return Statement::PrepareResult::SyntaxError;
    }
    int id;
    if (!absl::SimpleAtoi(v[1], &id)) {
      return Statement::PrepareResult::SyntaxError;
    };
    if (id < 0) {
      return Statement::PrepareResult::NegativeID;
    }
    auto username_sv = v[2];
    auto email_sv = v[3];
    if (username_sv.size() > Row::USERNAME_SIZE ||
        email_sv.size() > Row::EMAIL_SIZE) {
      return Statement::PrepareResult::StringTooLong;
    };
    row_to_insert_.id = id;
    strncpy(row_to_insert_.username, username_sv.data(), username_sv.size());
    row_to_insert_.username[username_sv.size()] = '\0';
    strncpy(row_to_insert_.email, email_sv.data(), email_sv.size());
    row_to_insert_.email[email_sv.size()] = '\0';
    return Statement::PrepareResult::Success;
  }
  if (absl::StartsWithIgnoreCase(line, "select")) {
    type_ = Statement::Type::Select;
    return Statement::PrepareResult::Success;
  }

  return Statement::PrepareResult::UnrecognizedStatement;
}
Statement::Type Statement::type() { return type_; }
