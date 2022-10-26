#ifndef SRC_HELPERS_DATAHENDLER_H_
#define SRC_HELPERS_DATAHENDLER_H_

#include "parser.h"

constexpr double kKoeff = 0.003921568;

namespace s21 {
class DataHandler {
  public:
    using parsed_data = std::vector<std::vector<int>>;
    using train_dataset = std::vector<double>;
    using train_answer = std::vector<double>;


  DataHandler(const std::string& file_name) {
    data_ = parser_.Parsing(file_name);
  }
  // pos should be 0 - 88800
  std::pair<train_dataset, train_answer> GetThisTrainSet(int pos) {
    if (parser_.get_error()) throw std::out_of_range("Couldnt parse file");
    if (pos < 0 || pos > 88800) throw std::length_error("There is no such train set");
    auto it = data_.begin() + pos;
    return NormalizeData_(*it);
  }

  private:
    parsed_data data_;
    Parser parser_;

    std::pair<train_dataset, train_answer> NormalizeData_(const std::vector<int>& parsed_data) {
      std::vector<double> answer(26, 0.0);
      answer[parsed_data[0] - 1] = 1.0;
      std::vector<double> normalized_input(parsed_data.size() - 1);
      auto it = parsed_data.begin() + 1;
      for (size_t i = 0; it != parsed_data.end(); ++it, ++i)
        normalized_input.at(i) = (double)*it * kKoeff;
      return {normalized_input, answer};
    }
};  // DataHandler
}  // namespace s21
#endif  // SRC_HELPERS_DATAHENDLER_H_