#include "../includes/network.h"
#include <vector>
#include <utility>

int main(int argc, char** argv) {
  if (argc > 1) {
    double alpha = stod(std::string(argv[1]));
    int train_set_percentage = stoi(std::string(argv[2]));
    int epochs = stoi(std::string(argv[3]));
    std::string weight_name = std::string(argv[1]) + "x" + std::string(argv[2]) + "x" + std::string(argv[3]);

    unsigned int start_time =  clock(); // начальное время
    s21::Network net({50, 30}, 784, 26, alpha);  // настройки
    net.Train(epochs, train_set_percentage);  // запустить тренировку
    net.SaveWeights(weight_name);  // сохранить веса
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time;
    std::cout << "\nIt tooks " << 1000.0 * search_time / CLOCKS_PER_SEC / 60000 << " mins to learn.";  
  } else {
    std::cout << "No settings in command line.";
  }
  return 0;
}
