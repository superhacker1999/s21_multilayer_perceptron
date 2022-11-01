#include "network.h"

int main() {
  s21::matrix::Network net({2}, 3, 1, 0.5);
  net.ForwardProp({1.0, 1.0, 1.0}).OutputMatrix();
  return 0;
}