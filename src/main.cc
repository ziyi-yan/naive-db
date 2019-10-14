#include <iostream>
#include <string>

#include "absl/strings/match.h"
#include "absl/strings/str_format.h"

#include "Executor.h"
#include "Statement.h"

enum class MetaCommandResult { Success, Unrecognized };

MetaCommandResult doMetaCommand(std::string line) {
  if (line == ".exit") {
    exit(EXIT_SUCCESS);
  } else {
    return MetaCommandResult::Unrecognized;
  }
}

int main() {
  Table tbl;

  std::string line;
  while (true) {
    // prompt for user input
    absl::PrintF("> ");
    if (!std::getline(std::cin, line)) {
      // failed to get the next user input
      exit(EXIT_FAILURE);
    }

    if (absl::StartsWith(line, ".")) {
      switch (doMetaCommand(line)) {
        case MetaCommandResult::Success:
          continue;
        case MetaCommandResult::Unrecognized:
          absl::PrintF("Unrecognized command '%s'\n", line);
          continue;
      }
    }

    Statement st{};
    switch (st.prepare(line)) {
      case Statement::PrepareResult::Success:
        break;
      case Statement::PrepareResult::SyntaxError:
        absl::PrintF("Syntax error. Could not parse statement.\n");
        continue;
      case Statement::PrepareResult ::UnrecognizedStatement:
        absl::PrintF("Unrecognized keyword at start of '%s'.\n", line);
        continue;
    }

    Executor ex;
    switch (ex.execute(st, &tbl)) {
      case Executor::ExecuteResult::Success:
        absl::PrintF("Executed.\n");
        break;
      case Executor::ExecuteResult::TableFull:
        absl::PrintF("Error: Table Full.\n");
        break;
    }
  }
}
