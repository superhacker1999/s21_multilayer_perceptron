#include <iostream>
#include "net.h"

int main() {
  std::vector<short> topology = {1, 1, 1, 1};
  s21::Net net(topology);
  int i = 0;
  while (i < 100) {
    std::vector<double> inputvals = {1.0};
    std::vector<double> answer = {0.001};
    net.FeedForward(inputvals);
    net.LearnProgressOutput(answer);
    ++i;
  }
  return 0;
}
