#include "../includes/network.h"
#include "../helpers/parser.h"
#include <vector>
#include <utility>

double GenerateNumber(double min, double max) {
  double random = (double) rand() / RAND_MAX;
  return min + random * (max - min);
}

std::pair<std::vector<double>, double> normalize_data (const std::vector<int>& parsed_data) {
  double answer = (double)parsed_data.front();
  std::vector<double> normalized_input(parsed_data.size() - 1);
  auto it = parsed_data.begin() + 1;
  // change to 255.0 for our task
  const double Koeff = 1.0;
  for (size_t i = 0; it != parsed_data.end(); ++it, ++i)
    normalized_input.at(i) = (double)*it / Koeff;
  return {normalized_input, answer};
}

int main() {
  int i = 0;
  // std::vector<double> input = {1.0};
  // 1. топология ВНУТРЕННИХ слоев,
  // 2. кол-во нейронов входящего слоя,
  // 3. кол-во нейронов выходящего слоя
  // 4. alhpa - learning rate
  s21::Network net({2}, 3, 1, 0.1);

  s21::Parser parser;
  s21::Parser::Dataset data = parser.Parsing("/Users/padmemur/Desktop/neuron_net/src3/dataset/XOR.csv");
  auto it = data.begin();
  while(i < 100000) {
    it += GenerateNumber(0, 7);
    std::pair<std::vector<double>, double> input_data = normalize_data(*it);
    std::vector<double> input = input_data.first;
    std::vector<double> expected{input_data.second};
    net.ForwardProp(input);
    net.BackProp(expected);
    net.UpdateWeights(input);
    net.LearnOutput(input, expected);
    ++i;
    it = data.begin();
  }
  std::cout<< "\nAll done!\n";
  std::vector<double> check;
  double num = 0;
  while (num >= 0) {
    std::cin >> num;
    check.push_back(num);
    std::cin >> num;
    check.push_back(num);
    std::cin >> num;
    check.push_back(num);
    std::cout<< "\nAnswer is: " << net.Predict(check);  
  }
}