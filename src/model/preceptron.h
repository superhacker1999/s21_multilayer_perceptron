//
// Created by Chastity Eryn on 10/14/22.
//

#ifndef MLP_S21_MULTILAYER_PERCEPTRON_SRC_MODEL_PRECEPTRON_H_
#define MLP_S21_MULTILAYER_PERCEPTRON_SRC_MODEL_PRECEPTRON_H_

#include <vector>
//  #include "Neuron.h"
//  typedef vector<Neuron> Layer;

using std::vector;

namespace s21 {

class Perceptron {
 public:
  Perceptron(vector<short> &topology);
  void GetResult();
  void BackPropagation();
  void SetFirstLayer(vector<double> input_value);

 private:
  size_t amount_of_hidden_layers_ = 2;
  double average_error_;

  //  возможна реализация с одним вектором, где лежать все слои
  Layer in_layer_;
  vector<Layer> hide_layer_;
  Layer out_layer_;

};

}

#endif //MLP_S21_MULTILAYER_PERCEPTRON_SRC_MODEL_PRECEPTRON_H_
