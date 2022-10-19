#include <iostream>
#include "net.h"
#include "parser.h"

std::vector<double> prepare_data(const std::vector<int>& data_line) {
  auto it = data_line.begin() + 1;
  std::vector<double> result_data(data_line.size() - 1);
  for (size_t i = 0; it != data_line.end(); ++it, ++i)
    result_data.at(i) = (double)*it;
  return result_data;
}

// int main() {
//   s21::Parser parser;
//   s21::Parser::Dataset data = parser.Parsing("/Users/padmemur/Desktop/neuron_net/dataset/XOR.csv");
  
//   std::vector<short> topology = {3, 2, 1};
//   s21::Net net(topology);
//   int i = 0;
//   while (i < 10000) {
//     // int index = s21::Neuron::RandomWeightGenerate_(7);
//     int index = 0;
//     std::vector<double> input = prepare_data(data[index]);
//     std::vector<double> answer(1, 0);
//     answer[0] = data[index][0] == 0 ? 0.0 : 1.0;
//     net.FeedForward(input);
//     net.BackProp(data[index][0] + 1);
//     net.UpdateWeights(input);
//     net.LearnProgressOutput(answer);
//     ++i;
//   }
//   return 0;
// }


int main() {  
  std::vector<short> topology = {1, 1, 1};
  s21::Net net(topology);
  int i = 0;
  while (i < 10000) {
    std::vector<double> input{1.0};
    std::vector<double> answer{1.0};
    net.FeedForward(input);
    net.BackProp(1);
    net.UpdateWeights(input);
    net.LearnProgressOutput(answer);
    ++i;
  }
  return 0;
}