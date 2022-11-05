#include "datahandler.h"

s21::DataHandler::DataHandler(const std::string &file_name)
    :  data_(parser_.Parsing(file_name)) {}

s21::DataHandler::DataHandler(const std::vector<int> &input_data) 
    : data_(std::vector<std::vector<int>>({input_data})) {}

std::vector<double> s21::DataHandler::normalizeInput() {
  std::vector<double> normalized_data;
  for (auto number : data_[0]) {
    normalized_data.push_back((double)number * kKoeff);
  }
  return normalized_data;
}

std::pair<std::vector<double>, std::vector<double>>
s21::DataHandler::GetThisTrainSet(int pos) {
  if (parser_.get_error())
    throw std::out_of_range("Couldnt parse file");
  if (pos < 0 || pos > 88800)
    throw std::length_error("There is no such train set");
  auto it = data_.begin() + pos;
  return NormalizeData_(*it);
}

std::pair<std::vector<double>, std::vector<double>>
s21::DataHandler::NormalizeData_(const std::vector<int> &parsed_data) {
  std::vector<double> answer(26, 0.0); // вектор с ответами
  answer[parsed_data[0] - 1] = 1.0; 
  // число с индексом ответа из первой строки parsed_data
  // становится единицей
  std::vector<double> normalized_input(parsed_data.size() - 1);
  auto it = parsed_data.begin() + 1;
  for (size_t i = 0; it != parsed_data.end(); ++it, ++i)
    normalized_input.at(i) = (double)*it * kKoeff;
  return {normalized_input, answer};
}
