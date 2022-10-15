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

namespace s21 {
class Neuron {
 public:
  Neuron(std::vector<int> topology, int layer_index, int index_in_layer);

  int GetMyIndex();
  double GetWeight();
  double GetValue();
  double GetError();

 private:
  int my_index_ = 0;
  double value_ = 0;
  double error_ = 0;

  double ActivationNeuron_(double summ_neuron_charges);
  double RandomWeightGenerate_();

 public:
  std::vector<Neuron> *previous_layer_;
  std::vector<Neuron> *next_layer_;
  std::vector<double> weight_;

  void FeedForward();
  void ConnectionNeuron(std::vector<Neuron> &previous_layer);
  void CalcLocalGradient(double right_value);


};
}  // namespace s21


#endif //S21_MULTILAYER_PERCEPTRON_NEURON_Hgit