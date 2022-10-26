#include "../includes/network.h"
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
  // net.Train(100);  // запустить тренировку
  // net.SaveWeights();  // сохранить веса
  net.UploadWeightsToNet(net.LoadWeights());  // загрузить выгруженные веса
  net.Test();  // запустить тест
}
