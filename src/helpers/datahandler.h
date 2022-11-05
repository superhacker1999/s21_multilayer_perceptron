#ifndef SRC_HELPERS_DATAHANDLER_H_
#define SRC_HELPERS_DATAHANDLER_H_

#include "parser.h"

constexpr double kKoeff = 0.003921568;

namespace s21 {
class DataHandler {
public:
  using parsed_data = std::vector<std::vector<int>>;
  using dataset = std::vector<double>;
  using answer = std::vector<double>;

  DataHandler(const std::string &file_name);
  DataHandler(const std::vector<int> &input_data);
  std::pair<dataset, answer> GetThisTrainSet(int pos);
  dataset normalizeInput();

private:
  parsed_data data_;
  Parser parser_;

  std::pair<dataset, answer>
  NormalizeData_(const std::vector<int> &parsed_data);
}; // DataHandler
} // namespace s21
#endif // SRC_HELPERS_DATAHANDLER_H_
