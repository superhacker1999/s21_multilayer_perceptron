#include "network.h"


// spec = {50, 50}
// input_size = 784
// num_classes = 26
// learning_rate = 0.05
s21::matrix::Network::Network(std::vector<int> spec, size_t input_size,
size_t num_classes, double learning_rate) : m_alpha_(learning_rate) {
  InitializeLayers_(spec, input_size, num_classes);
  InitializeWeights_();
}

s21::matrix::Network::~Network() {
  for (size_t i = 0; i < m_layers_.size(); ++i)
    delete m_layers_.at(i);
  for (size_t i = 0; i < m_weigths_.size(); ++i)
    delete m_weigths_.at(i);
}

void s21::matrix::Network::InitializeLayers_(const std::vector<int>& spec,
                                size_t input_size, size_t num_classes) {
  m_layers_.reserve(spec.size() + 2);
  m_layers_.push_back(new S21Matrix(1, input_size));  // adding input layer
  for (size_t i = 0; i < spec.size(); ++i)  // adding hidden layers
    m_layers_.push_back(new S21Matrix(1, spec.at(i)));
  m_layers_.push_back(new S21Matrix(1, num_classes));  // adding output layer
}

void s21::matrix::Network::InitializeWeights_() {
  m_weigths_.reserve(m_layers_.size() - 1);
  for (size_t i = 1; i < m_layers_.size(); ++i) {
    m_weigths_.push_back(new S21Matrix(  // adding weights
      m_layers_.at(i - 1)->GetRows() + 1, m_layers_.at(i)->GetRows())
    );  // GetRows + 1 cuz we need one more weight (bias)
    // initializing it with random weights
    m_weigths_.at(i - 1)->FillMatrix(true);
  }
}

std::vector<double> s21::matrix::Network::ForwardProp(const std::vector<double>& input_data) {
  
}
