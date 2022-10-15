//
// Created by Rebbecca Gormond aka Mikhail Kukhtachev on 10/4/22.
//

#include "parser.h"

namespace s21 {

Parser::Dataset Parser::Parsing(const std::string &file_name) {
    std::string line;
    std::ifstream file(file_name);
    error_ = false;
    if (file.is_open()) {
        while (getline(file, line)) {
            data_set_.push_back(StringParsing_(line));
//            count_string++; // delete late
        }
        data_set_.shrink_to_fit();
        file.close();
    } else {
        error_ = true;
    }
    return data_set_;
}

std::vector<double> Parser::getTargetOutputs(const std::vector<int>& data_line) {
  std::vector<double> target_outputs(26);
  for(auto it = target_outputs.begin(); it != target_outputs.end(); ++it)
    *it = 0.0f;
  target_outputs[data_line[0] - 1] = 1.0f;
  return target_outputs;
}

std::vector<double> Parser::getInputVals(const std::vector<int>& data_line) {
  auto it = data_line.begin();
  it++;
  std::cout<<"\n\n"<<data_line.size()<<"\n\n";
  std::vector<double> input_vals(data_line.size() - 1);
  for(int i = 0; it != data_line.end(); ++it, ++i) {
    input_vals[i] = *it * kKoeff;
  }
  return input_vals;
}

std::vector<int> Parser::StringParsing_(std::string line) {
    std::vector<int> result_vector;
    result_vector.reserve(string_size_);
    std::string tmp_sub_string;
    for(auto it = line.begin(); it <= line.end(); ++it) {
        if(isdigit(*it)) {tmp_sub_string += *it;}
        if((*it == ',' || it == line.end()) && !tmp_sub_string.empty()) {
            result_vector.push_back(std::stoi(tmp_sub_string));
            tmp_sub_string.clear();
        }
    }
//    result_vector.shrink_to_fit(); // ?
    string_size_ = result_vector.size();
    return result_vector;
}

void Parser::Print() {  // delete late
    for(auto i = 0; i < data_set_.size(); ++i) {
        for(int j = 0; j < data_set_[i].size(); ++j)
            std::cout << data_set_[i][j] << ' ';
        std::cout << std::endl;
    }
}

}  // namespace s21
