#ifndef SRC_HELPERS_DATAHANDLER_H_
#define SRC_HELPERS_DATAHANDLER_H_

#include "parser.h"

constexpr double kKoeff = 0.003921568;

namespace s21 {
class DataHandler {
public:
  using parsed_data = std::vector<std::vector<int>>;
  using train_dataset = std::vector<double>;
  using train_answer = std::vector<double>;

  DataHandler(const std::string &file_name);
  std::pair<train_dataset, train_answer> GetThisTrainSet(int pos);
  void parseData();

private:
  std::string file_path_;
  parsed_data data_;
  Parser parser_;

  std::pair<train_dataset, train_answer>
  NormalizeData_(const std::vector<int> &parsed_data);
}; // DataHandler
} // namespace s21
#endif // SRC_HELPERS_DATAHANDLER_H_