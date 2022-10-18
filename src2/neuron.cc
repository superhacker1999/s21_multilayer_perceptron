#include "neuron.h"

s21::Neuron::Neuron(const std::vector<short>& topology,
      size_t layer_index, size_t index_in_layer) {
  m_index_ = index_in_layer;
  if (layer_index != topology.size() - 1) {
    for (short i = 0; i < topology[layer_index]; ++i)
      m_weight_.push_back(0.1f);
  }
  m_weight_.shrink_to_fit();
}

double s21::Neuron::ActivationNeuron_(double x) {
  return x / (1 + fabs(x));
}

double s21::Neuron::RandomWeightGenerate_() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> dist(0, 1000);
  return static_cast<double>(dist(engine))/1000000;
}