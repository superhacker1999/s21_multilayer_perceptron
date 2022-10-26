//
// Created by Rebbecca Gormond aka Mikhail Kukhtachev on 10/4/22.
//

#ifndef MODEL_PARSER_H
#define MODEL_PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace s21 {

class Parser {
  private:
    bool error_;
    int string_size_ = 0;
    

    std::vector<int> StringParsing_ (std::string line);

  public:
    using Dataset = std::vector<std::vector<int>>;
    Parser() : error_(false) {}
    ~Parser() {}

    int count_string = 0;

    Dataset Parsing(const std::string &file_name);
    void Print();
    Dataset data_set_;

    [[nodiscard]] bool get_error() const { return error_; };
};
}  // namespace s21

#endif //MODEL_PARSER_H
