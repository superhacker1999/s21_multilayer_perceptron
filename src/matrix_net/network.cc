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
      m_layers_.at(i - 1)->GetCols(), m_layers_.at(i)->GetCols()));
    m_weigths_.at(i - 1)->FillMatrix(true);
  }
}

void s21::matrix::Network::InitializeDeltas_() {
  m_deltas_.reserve(m_layers_.size() - 1);
  for (size_t i = 1; i < m_layers_.size(); ++i)
    m_deltas_.push_back(new S21Matrix(  // adding weights
      m_layers_.at(i - 1)->GetCols(), m_layers_.at(i)->GetCols()));
}

double s21::matrix::Network::TransferDerivative(double value) {
  return value * (1.0 - value);
}

S21Matrix s21::matrix::Network::ForwardProp(const std::vector<double>& input_data) {
  m_layers_.front()->SetValues(input_data);
  for (size_t i = 0; i < m_layers_.size() - 1; ++i) {
    *m_layers_.at(i + 1) = m_layers_.at(i)->MulMatrix(
                          *m_weigths_.at(i));
    m_layers_.at(i + 1)->TransferMatrix();
  }
  return *(m_layers_.back());
}

// void s21::matrix::Network::BackProp(const std::vector<double>& expected) {
//   double error;
//   std::vector<double> deltas;
//   // for every layer starting from the end to the begin
//   for (size_t i = m_layers_.size() - 1; i != 0; --i) {
//     if (i == m_layers_.size() - 1) {
//       // for every value in the output layer
//       // searching for delta_weight
//       for (size_t j = 0; j < m_layers_[i]->GetCols(); ++j) {
//         double neuron_val = (*m_layers_[i])(0, j);  // (1, j) ??
//         error = (neuron_val - expected[j]);
//         deltas.push_back(error * TransferDerivative(neuron_val));
//       }
//     } else {
//       // searching for deltas in the hidden layers

//     }
//     // getting new weights using deltas
//     S21Matrix *curr_w_mtrx = m_weigths_.at(i - 1);
//     // for every weight in the current weights' matrix
//     // update weights
//     for (size_t j = 0; j < curr_w_mtrx->GetRows(); ++j) {
//       for (size_t k = 0; k < curr_w_mtrx->GetCols(); ++k) {
//         // w_n = w_n - val_n * delta_n * alpha
//         // новый вес -=
//         // - [значение нейрона в левом слое привязанного к этому весу]
//         // * [дельту нейрона в правом слое привязанного к этому весу]
//         // * [альфу]
//         (*curr_w_mtrx)(j, k) = (*curr_w_mtrx)(j, k) - (*m_layers_[i - 1])(0, k) * deltas[k] * m_alpha_;
//       }
//     }
//     deltas.clear();
//   }
// }

void s21::matrix::Network::BackProp(const std::vector<double>& expected) {
  for (size_t i = m_layers_.size() - 1; i != 0; --i) {
    std::vector<double> errors;
    if (i == m_layers_.size() - 1) {
      for (size_t j = 0; j < m_layers_[i]->GetCols(); ++j)
        errors.push_back((*m_layers_[i])(0, j) - expected[j]);
    } else {
      for (size_t j = 0; j < m_weigths_[i]->GetRows(); ++j) {
        double error = 0.0;
        for (size_t k = 0; k < m_weigths_[i]->GetCols(); ++k) {
          error += (*m_weigths_[i])(j, k) * (*m_deltas_[i])(j, k);
        }
        errors.push_back(error);
      }
    }
    for (size_t j = 0; j < (*m_deltas_[i - 1]).GetRows(); ++j) {
      for (size_t k = 0; k < (*m_deltas_[i - 1]).GetCols(); ++k) {
        // супер-пупер не уверен на счет j k && etc.
        (*m_deltas_[i - 1])(j, k) = errors[j] * (*m_layers_[i])(0, j);
      }
    }
  }
}

