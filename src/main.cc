#include <iostream>
#include <string>

#include "absl/strings/str_format.h"

int main() {
  std::string line;
  while (true) {
    // prompt for user input
    absl::PrintF("> ");
    if (!std::getline(std::cin, line)) {
      // failed to get the next user input
      exit(EXIT_FAILURE);
    }

    if (line == ".exit") {
      exit(EXIT_SUCCESS);
    } else {
      absl::PrintF("Unrecognized command '%s'.\n", line);
    }
  }
  return 0;
}
