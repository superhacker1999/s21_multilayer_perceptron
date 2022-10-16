//
// Created by Rebbecca Gormond aka Mikhail Kukhtachev on 10/14/22.
//

#include "neuron.h"
namespace s21 {
Neuron::Neuron(std::vector<int> topology, size_t layer_index, size_t index_in_layer) {  // тут нужна проверка на nullptr
  my_index_ = index_in_layer;
  // if(layer_index != 0) previous_layer_->reserve(topology[layer_index - 1]);
  // if(layer_index != topology.size() - 1) next_layer_->reserve(topology[layer_index + 1]);
  weight_.reserve(topology[layer_index]);
  for(int i = 0; i < topology[layer_index]; i++)
    weight_.push_back(RandomWeightGenerate_());
}

void Neuron::FeedForward() {
  double accumulate_charge = 0;
  for(size_t i = 0; i < previous_layer_->size(); i++)
    accumulate_charge += previous_layer_->at(i).weight_[my_index_] * previous_layer_->at(i).value_;
  this->value_ = ActivationNeuron_(accumulate_charge);
}

void Neuron::ConnectionNeuron(std::vector<Neuron> *previous_layer) {
  previous_layer_ = previous_layer;
}

double Neuron::ActivationNeuron_(double summ_neuron_charges) {
  // return 1 / 1 + exp((-1) * summ_neuron_charges);
  return 1.0 / (1.0 + exp(-summ_neuron_charges));
}

double Neuron::ActivationDerivativeNeuron_(double value) {
  return value * (1.0 - value);
}

double Neuron::RandomWeightGenerate_() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> dist(0, 1000);
  return static_cast<double>(dist(engine))/1000;
}

//  локальная ошибка конкретно у этого нейрона
void Neuron::CalcLocalGradient(double right_value) {
  double delta = right_value - value_;
  delta_ = delta * ActivationNeuron_(value_);
}

double Neuron::GetValue() {
  return this->value_;
}

double Neuron::GetDelta() {
  return this->delta_;
}

void Neuron::SetDelta(double delta) {
  this->delta_ = delta;
}

int Neuron::GetMyIndex() {
  return this->my_index_;
}

void Neuron::setValue(double val) {
  this->value_ = val;
}

double& Neuron::GetWeight(size_t index) {
  return this->weight_[index];
}

// double Neuron::GetWeight(int index) {} // дописать.

}  // namespace s21