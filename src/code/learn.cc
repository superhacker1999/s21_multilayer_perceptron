#include "../includes/network.h"
#include <vector>
#include <utility>

int main(int argc, char** argv) {
  
  unsigned int start_time =  clock(); // начальное время
  s21::Network net({50, 30}, 784, 26, 0.05);  // настройки
  net.Train(100);  // запустить тренировку
  net.SaveWeights();  // сохранить веса
  unsigned int end_time = clock(); // конечное время
  unsigned int search_time = end_time - start_time;
  std::cout << "\nIt tooks " << 1000.0 * search_time / CLOCKS_PER_SEC / 60000 << " mins to learn.";
}
