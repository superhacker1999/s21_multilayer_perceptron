#include "../includes/network.h"
#include "../helpers/parser.h"
#include <vector>
#include <utility>

double GenerateNumber(double min, double max) {
  double random = (double) rand() / RAND_MAX;
  return min + random * (max - min);
}

std::pair<std::vector<double>, std::vector<double>> normalize_data (const std::vector<int>& parsed_data) {
  std::vector<double> answer(26, 0.0);
  answer[parsed_data[0] - 1] = 1.0;
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
  s21::Network net({100, 100}, 784, 26, 0.1);

  s21::Parser parser;
  s21::Parser::Dataset data = parser.Parsing("/Users/padmemur/Desktop/neuron_net/dataset/emnist-letters-train.csv");
  auto it = data.begin();
  // int min = 0;
  // int max = 1000;
  double error = 0.0;
  int a = 0;
  while(i < 1) {
    // it += GenerateNumber(min, max);
    std::pair<std::vector<double>, std::vector<double>> input_data = normalize_data(*it);
    std::vector<double> input = input_data.first;
    std::vector<double> expected = input_data.second;
    net.ForwardProp(input);
    net.BackProp(expected);
    net.UpdateWeights(input);
    error = net.LearnOutput(input, expected);
    if (error < 0.01) {
      ++i;
    }
    // it = data.begin();
    
    std::cout<< std::endl << a++ << std::endl;
    ++it;
    if (it == data.end()) break;
  }
  std::cout<< "\nAll done!\n";
}