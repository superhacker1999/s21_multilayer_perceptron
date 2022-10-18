//
// Created by Chastity Eryn on 10/14/22.
//

#ifndef MLP_S21_MULTILAYER_PERCEPTRON_SRC_MODEL_PRECEPTRON_H_
#define MLP_S21_MULTILAYER_PERCEPTRON_SRC_MODEL_PRECEPTRON_H_

#include <vector>
#include <stdexcept>
#include <cassert>

#include "neuron.h"

using std::vector;
typedef vector<s21::Neuron> Layer;

namespace s21 {

class Perceptron {
 public:
  Perceptron(vector<int> &topology);
  double GetResult(int index_neuron);
  double GetError();
  void BackPropagation(const int& answer_pos);
  void FeedForward(const vector<double> &input_value);
  void UpdateWeight(const vector<double> &input_value);
  void LearnProgressOutput(const std::vector<double>& expected);

 private:
  int amount_of_hidden_layers_ = 2;
  double error_;
  double average_error_;
  const double kALPHA = 0.1f;
  vector<Layer> layers_;

  //  возможна реализация с одним вектором, где лежать все слои
//  Layer in_layer_;
//  vector<Layer> hide_layer_;
//  Layer out_layer_;

};

}

#endif //MLP_S21_MULTILAYER_PERCEPTRON_SRC_MODEL_PRECEPTRON_H_
