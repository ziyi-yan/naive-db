#include "absl/strings/str_format.h"

#include "Executor.h"

void Executor::execute(Statement st) {
  switch (st.type()) {
    case (Statement::Type::Insert):
      absl::PrintF("This is where we would do an insert.\n");
      break;
    case (Statement::Type::Select):
      absl::PrintF("This is where we would do a select.\n");
      break;
  }

}
