#include "datahandler.h"

s21::DataHandler::DataHandler(const std::string &file_name) : file_path_(file_name) {}

void s21::DataHandler::parseData() {
    data_ = parser_.Parsing(file_path_);
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
