#include "perceptron.h"
#include <vector>
#include "helpers/parser.h"
#include <iostream>

std::vector<double> prepare_data(const std::vector<int>& data_line) {
  auto it = data_line.begin() + 1;
  std::vector<double> result_data(data_line.size() - 1);
  for (size_t i = 0; it != data_line.end(); ++it, ++i)
    result_data.at(i) = (double)*it;
  return result_data;
}

int main() {
  std::vector<int> topology = {1, 1, 1, 1};
  s21::Perceptron Net(topology);
  // s21::Parser::Dataset data{{0,0,0}, {1,0,1}, {1,1,0}, {0,1,1}};
  // s21::Parser parser;
  // s21::Parser::Dataset data = parser.Parsing("/Users/padmemur/Desktop/neuron_net/src/model/emnist-letters-train.csv");
  s21::Parser::Dataset data = {{0, 1}, {0, 1}, {1, 0}, {1, 1}};

  auto it = data.begin();
  int i = 0;

  // while(i < 10) {
  //   std::vector<double> input_vals = prepare_data(*it);
  //   std::vector<double> answer(1, 0);
  //   answer[it.base()->at(0) == 0 ? 0 : 1] = 0.0001;
  //   Net.FeedForward(input_vals);
  //   Net.BackPropagation(it.base()->at(0));
  //   Net.UpdateWeight(input_vals);
  //   Net.LearnProgressOutput(answer);
  //   // it++;
  //   i++;
  // }
  while(i < 10) {
    std::vector<double> input_vals{1.0};
    std::vector<double> answer{0.0001};
    Net.FeedForward(input_vals);
    // Net.BackPropagation(it.base()->at(0));
    // Net.UpdateWeight(input_vals);
    Net.LearnProgressOutput(answer);
    // it++;
    i++;
  }
}