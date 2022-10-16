//
// Created by Rebbecca Gormond aka Mikhail Kukhtachev on 10/4/22.
//

#include "parser.h"

namespace s21 {

s21::Parser::Dataset Parser::Parsing(const std::string &file_name) {
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

std::vector<int> Parser::StringParsing_(std::string line) {
    std::vector<int> result_vector;
    result_vector.reserve(string_size_);
    std::string tmp_sub_string;
    for(auto it = line.begin(); it <= line.end(); it++) {
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
    for(size_t i = 0; i < data_set_.size(); i++) {
        for(size_t j = 0; j < data_set_[i].size(); j++)
            std::cout << data_set_[i][j] << ' ';
        std::cout << std::endl;
    }
}

}  // namespace s21
