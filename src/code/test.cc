#include "../includes/network.h"
#include <vector>
#include <utility>

int main(int argc, char** argv) {
  if (argc > 0) {
    s21::Network net({50, 30}, 784, 26, 0.05);
    net.UploadWeightsToNet(net.LoadWeights(argv[1]));  // загрузить выгруженные веса
    net.Test();  // запустить тест  
  }
  return 0;
}
