#include <iostream>
#include <string>

#include "absl/strings/match.h"
#include "absl/strings/str_format.h"

#include "Executor.h"
#include "Statement.h"

enum class MetaCommandResult { Success, Unrecognized, Exit };

MetaCommandResult parseMetaCommand(std::string line) {
  if (line == ".exit") {
    return MetaCommandResult::Exit;
  } else {
    return MetaCommandResult::Unrecognized;
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    absl::PrintF("Must supply a database filename.\n");
    exit(EXIT_FAILURE);
  }

  char* filename = argv[1];


  Table tbl{filename};

  std::string line;
  bool exiting = false;
  while (!exiting) {
    // prompt for user input
    absl::PrintF("db > ");
    if (!std::getline(std::cin, line)) {
      // failed to get the next user input
      exit(EXIT_FAILURE);
    }

    if (absl::StartsWith(line, ".")) {
      switch (parseMetaCommand(line)) {
        case MetaCommandResult::Success:
          continue;
        case MetaCommandResult::Exit:
          exiting = true;
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
      case Statement::PrepareResult::StringTooLong:
        absl::PrintF("String is too long.\n");
        continue;
      case Statement::PrepareResult::NegativeID:
        absl::PrintF("ID must be positive.\n");
        continue;
      case Statement::PrepareResult::UnrecognizedStatement:
        absl::PrintF("Unrecognized keyword at start of '%s'.\n", line);
        continue;
    }

    Executor ex;
    switch (ex.execute(st, &tbl)) {
      case Executor::ExecuteResult::Success:
        absl::PrintF("Executed.\n");
        break;
      case Executor::ExecuteResult::TableFull:
        absl::PrintF("Error: Table full.\n");
        break;
    }
  }
}
