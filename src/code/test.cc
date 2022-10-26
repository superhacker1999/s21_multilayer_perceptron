#include "../includes/network.h"
#include "../helpers/datahendler.h"
#include <vector>
#include <utility>

double GenerateNumber(double min, double max) {
  double random = (double) rand() / RAND_MAX;
  return min + random * (max - min);
}

int main() {
 // std::vector<double> input = {1.0};
 // 1. топология ВНУТРЕННИХ слоев,
 // 2. кол-во нейронов входящего слоя,
 // 3. кол-во нейронов выходящего слоя
 // 4. alhpa - learning rate
  s21::Network net({50, 30}, 784, 26, 0.1);
  s21::DataHandler data_handler("/Users/padmemur/Desktop/neuron_net/dataset/emnist-letters-train.csv");

  // learn case 1
  // int i = 0;
  // int index = 0;
  // double error = 0.0;
  // int a = 0;
  // int start = 0;
  // while(i < 1) {
  //   auto input_data = data_handler.GetThisTrainSet(index);
  //   std::vector<double> input = input_data.first;
  //   std::vector<double> expected = input_data.second;
  //   net.ForwardProp(input);
  //   net.BackProp(expected);
  //   net.UpdateWeights(input);
  //   error = net.LearnOutput(expected);
  //   if (error < 0.002) {
  //     ++i;
  //   }
  //   std::cout << std::endl << a++ << std::endl;
  //   start = a % 102 > 100 ? start + 26 : start;
  //   index = index % 27 > 25 ? start : ++index;
  // }

  // learn case 2

  int index = 0;
  int epochs = 0;

  while(epochs < 100) {
    auto input_data = data_handler.GetThisTrainSet(index);
    std::vector<double> input = input_data.first;
    std::vector<double> expected = input_data.second;
    net.ForwardProp(input);
    net.BackProp(expected);
    net.UpdateWeights(input);
    net.LearnOutput(expected);
    if (index == 4440) {
      index = 0;
      ++epochs;
    } else {
      index++;
    }
    std::cout << std::endl << epochs << std::endl;
  }
  // save weights
  std::cout<< "\nAll done!\n";
}