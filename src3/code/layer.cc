#include "../includes/layer.h"

s21::Layer::Layer(size_t prev_layer_size, size_t curr_layer_size) {
  for (size_t i = 0; i < curr_layer_size; ++i) {
    m_neurons_.push_back(new Neuron(prev_layer_size));
  }
  m_current_layer_size_ = curr_layer_size; 
}