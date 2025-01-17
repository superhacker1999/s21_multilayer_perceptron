#include "../includes/neuron.h"
#include <random>

double GenerateRandomNumber(double min, double max) {
  double random = (double) rand() / RAND_MAX;
  return min + random * (max - min);
}

s21::Neuron::Neuron(size_t prev_layer_size) {
  InitializeWeights_(prev_layer_size);
}

void s21::Neuron::InitializeWeights_(size_t prev_layer_size) {
  std::default_random_engine generator;
  std::normal_distribution<double> dis(0.0, 1.0);
  for(size_t i = 0; i < prev_layer_size + 1; ++i) {
    m_weights_.push_back(GenerateRandomNumber(-1.0, 1.0));
  }
}