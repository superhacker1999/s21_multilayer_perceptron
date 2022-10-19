#include "neuron.h"

s21::Neuron::Neuron(const std::vector<short>& topology,
      size_t layer_index, size_t index_in_layer) {
  m_index_ = index_in_layer;
  // topology[layer_index] + 1 cuz we need 1 more neuron - bias
  for (short i = 0; i < topology[layer_index] + 1; ++i)
    m_weight_.push_back(0.1);
  m_weight_.shrink_to_fit();
}

double s21::Neuron::RandomWeightGenerate_(int x) {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> dist(0, x);
  return static_cast<double>(dist(engine))/((x == 1000) ? x : 1);
}
