//
// Created by Rebbecca Gormond aka Mikhail Kukhtachev on 10/14/22.
//

#ifndef S21_MULTILAYER_PERCEPTRON_NEURON_H
#define S21_MULTILAYER_PERCEPTRON_NEURON_H

#include <vector>
#include <cstdlib>
#include <random>
#include <iostream>
#include <cmath>
#include <cassert>

namespace s21 {
  class Neuron;
}

using std::vector;
typedef vector<s21::Neuron> Layer;

namespace s21 {
class Neuron {
 public:
  Neuron(std::vector<int> topology, size_t layer_index, size_t index_in_layer);
  Neuron(const Neuron& other) {
    my_index_ = other.my_index_;
    value_ = other.value_;
    delta_ = other.delta_;
    previous_layer_ = other.previous_layer_;
    next_layer_ = other.next_layer_;
    weight_ = other.weight_;
  }
  Neuron(Neuron&& other) {
    my_index_ = other.my_index_;
    value_ = other.value_;
    delta_ = other.delta_;
    previous_layer_ = other.previous_layer_;
    next_layer_ = other.next_layer_;
    weight_ = other.weight_;
    other.previous_layer_ = nullptr;
    other.next_layer_ = nullptr;
  }
  void operator=(const Neuron&) {

  }
  ~Neuron() {;}

  int GetMyIndex();
  double& GetWeight(size_t index);
  double GetValue();
  double GetError();
  void setValue(double value);

 public:
  int my_index_ = 0;
  double value_ = 0.0;
  double delta_ = 0.0;
  std::vector<Neuron>* previous_layer_ = nullptr;
  std::vector<Neuron>* next_layer_;
  std::vector<double> weight_;

public:
  double ActivationNeuron_(double summ_neuron_charges);
  static double ActivationDerivativeNeuron_(double value);
  double RandomWeightGenerate_();

  public:
    void FeedForward();
    void ConnectionNeuron(std::vector<Neuron> *previous_layer);
    void CalcLocalGradient(double right_value);
    double GetDelta();
    void SetDelta(double delta);



};
}  // namespace s21


#endif //S21_MULTILAYER_PERCEPTRON_NEURON_Hgit