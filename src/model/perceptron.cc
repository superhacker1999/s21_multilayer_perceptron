//
// Created by Chastity Eryn on 10/14/22.
//

#include "perceptron.h"

using namespace s21;

//  инициализация нейронной сети рандомными весами
//  расстановка размеров
//  остальное происходит в классе нейрона
Perceptron::Perceptron(vector<int> &topology) {
  for (size_t layer_num = 0; layer_num < topology.size(); layer_num++) {
    layer_.push_back(Layer());
    for (size_t neuron_num = 0; neuron_num < topology[layer_num]; neuron_num++) {
//  конструктор нейрона, отдаем топологию и индекс текущего слоя
        layer_.back().push_back(Neuron(topology, layer_num, neuron_num));
    }
  }
}

//  продвижение вперед по слоям, расстановка значений в нейронах, активайция?
void Perceptron::FeedForward(vector<double> &input_value) {
  if (input_value.size() != layer_[0].size())
    throw std::length_error("Error! Wrong size input value");

  //  установка значений первого слоя
  for (size_t i = 0; i < input_value.size(); i++)
    layer_[0][i].setValue(input_value[i]);

  for (size_t layer_num = 1; layer_num < layer_.size(); layer_num++) {
    //  сделали вывод, что он не нужен
//    Layer &prev_layer = layer_[layer_num - 1];

    //  продвижение вперед у нейрона
    //  он идет по нейронам предыдущего слоя, *какие-то формулы*
    for (size_t neuron_num = 0; neuron_num < layer_[layer_num].size() - 1; neuron_num++)
      layer_[layer_num][neuron_num].FeedForward();
//      layer_[layer_num][neuron_num].FeedForward(prev_layer);

  }
}

void Perceptron::BackPropagation(const vector<double> &right_value) {
  Layer &output_layer = layer_.back();
  error_ = 0.0;

  for (size_t neuron = 0; neuron < output_layer.size(); neuron++) {
    double delta = right_value[neuron] - output_layer[neuron].GetValue();
    error_ += delta * delta;
  }
  error_ /= 2;

  //  считаем локальный градиент
  for (size_t neuron = 0; neuron < output_layer.size(); neuron++)
    output_layer[neuron].CalcLocalGradient(right_value[neuron]);

  //  градиент скрытых слоев
  for (size_t layer_num = layer_.size() - 2; layer_num > 0; layer_num--) {

  }
}

//  получение значений нейронов на последнем слое
double Perceptron::GetResult(int index_neuron) {
  return layer_.back()[index_neuron].GetValue();
}

double Perceptron::GetError() {
  return average_error_;
}

//  мне нужен из нейрона
//  GetValue
//  FeedForward
//  constructor (topology, index_l, index_n)