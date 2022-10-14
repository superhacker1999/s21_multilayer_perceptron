#include <iostream>
#include <cmath>
#include <cstdlib>

void prepareDataForXOR() {
  std::cout<<"topology: 2 4 1" << std::endl;

  for (int i = 2000; i >= 0; --i) {
    int n1 = (int)(2.0 * rand() / double(RAND_MAX));
    int n2 = (int)(2.0 * rand() / double(RAND_MAX));
    int res = n1 ^ n2;
    std::cout << "in: " << n1 << ".0 " << n2 << ".0" << std::endl;
    std::cout<< "out: " << res << ".0" << std::endl;
  }
}

void prepareDataForPerimiter() {
  std::cout<<"topology: 2 4 1" << std::endl;

  for (int i = 100000; i >= 0; --i) {
    double n1 = (2.0 * rand() / double(RAND_MAX));
    double n2 = (2.0 * rand() / double(RAND_MAX));
    double res = n1 - n2;
    printf("in: %.5lf %.5lf\nout: %5lf\n", n1, n2, res);
  }
}

int main(int argc, char** argv) {
  if (std::string(argv[1]) == "XOR")
    prepareDataForXOR();
  else
    prepareDataForPerimiter();
}
