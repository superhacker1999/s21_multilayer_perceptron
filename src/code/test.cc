#include "../includes/network.h"
#include <vector>
#include <utility>

int main() {
  s21::Network net({50, 30}, 784, 26, 0.05);
  net.UploadWeightsToNet(net.LoadWeights("weights8880x100x005.txt"));  // загрузить выгруженные веса
  net.Test();  // запустить тест
}
