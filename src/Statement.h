#ifndef NAIVE_DB_STATEMENT_H
#define NAIVE_DB_STATEMENT_H
#include <string>
struct Statement {
 public:
  enum class PrepareResult { Success, UnrecognizedStatement };
  enum class Type { Insert, Select };

  Type type();

  PrepareResult prepare(std::string_view line);

 private:
  Type type_;
};

#endif  // NAIVE_DB_STATEMENT_H
