#include "../includes/layer.h"

s21::Layer::Layer(size_t prev_layer_size, size_t curr_layer_size) {
  for (size_t i = 0; i < curr_layer_size; ++i) {
    // создаем нейрон в котором хранится массив весов
    m_neurons_.push_back(new Neuron(prev_layer_size));
  }
  m_current_layer_size_ = curr_layer_size; 
}

s21::Layer::~Layer() {
  for (size_t i = 0; i < m_neurons_.size(); ++i) {
    delete m_neurons_[i];
  }
}