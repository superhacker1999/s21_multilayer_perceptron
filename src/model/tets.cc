#include <vector>
#include <iostream>

int main() {
  std::vector<double> arr;
  std::cout<<arr.size()<<"  "<<arr.capacity()<<std::endl;
  arr.reserve(1);
  std::cout<<arr.size()<<"  "<<arr.capacity()<<std::endl;
  arr.push_back(1);
  std::cout<<arr.size()<<"  "<<arr.capacity()<<std::endl;
}