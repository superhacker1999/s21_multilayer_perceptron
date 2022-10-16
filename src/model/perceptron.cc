//
// Created by Chastity Eryn on 10/14/22.
//

#include "perceptron.h"

using namespace s21;

//  инициализация нейронной сети рандомными весами
//  расстановка размеров
//  остальное происходит в классе нейрона
Perceptron::Perceptron(vector<int> &topology) {
  for (size_t layer_num = 0; layer_num < topology.size(); ++layer_num) {
    layer_.push_back(Layer());
    for (int neuron_num = 0; neuron_num < topology[layer_num]; ++neuron_num) {
//  конструктор нейрона, отдаем топологию и индекс текущего слоя
        layer_[layer_num].push_back(Neuron(topology, layer_num, neuron_num));
    }
  }
}

//  продвижение вперед по слоям, расстановка значений в нейронах, активайция?
void Perceptron::FeedForward(const vector<double> &input_value) {
  // assert(input_value.size() == 784);
  if (input_value.size() != layer_[0].size())
    throw std::length_error("Error! Wrong size input value");

  //  установка значений первого слоя
  for (size_t i = 0; i < input_value.size(); ++i)
    layer_[0][i].setValue(input_value[i]);

  for (size_t layer_num = 1; layer_num < layer_.size(); ++layer_num) {
    //  сделали вывод, что он не нужен
//    Layer &prev_layer = layer_[layer_num - 1];

    //  продвижение вперед у нейрона
    //  он идет по нейронам предыдущего слоя, *какие-то формулы*
    for (size_t neuron_num = 0; neuron_num < layer_[layer_num].size() - 1; ++neuron_num) {
      layer_[layer_num][neuron_num].ConnectionNeuron(&layer_[layer_num - 1]);
      layer_[layer_num][neuron_num].FeedForward();
    }
  }
}

void Perceptron::BackPropagation(const int& answer_pos) {
  // Layer &output_layer = layer_.back();
  // error_ = 0.0;

  // for (size_t neuron = 0; neuron < output_layer.size(); ++neuron) {
  //   double delta = right_value[neuron] - output_layer[neuron].GetValue();
  //   error_ += delta * delta;
  // }
  // error_ /= 2;

  // //  считаем локальный градиент
  // for (size_t neuron = 0; neuron < output_layer.size(); ++neuron)
  //   output_layer[neuron].CalcLocalGradient(right_value[neuron]);

  // //  градиент скрытых слоев
  // for (size_t layer_num = layer_.size() - 2; layer_num > 0; --layer_num) {

  // }
  std::vector<double> answer(26, 0);
  answer[answer_pos - 1] = 1.0;
  for (int i = amount_of_hidden_layers_; i >= 0; --i) {
    std::vector<double> errors;
    if (i != amount_of_hidden_layers_) {
      for (size_t j = 0; j < layer_[i + 1].size(); ++j) {
        double error = 0.0;
        for (Neuron neuron : layer_[i + 1]) {
          double temp_error = neuron.GetWeight(j) * neuron.GetDelta();
          error += temp_error;
        }
        errors.push_back(error);
      }
    } else {
      for (size_t j = 0; j < layer_[i].size(); ++j) {
        errors.push_back(layer_[i][j].GetValue() - answer[j]);
      }
    }
    for (size_t j = 0; j < layer_[i].size(); ++j) {
      Neuron neuron = layer_[i][j];
      double num1 = errors[j];
      double num = neuron.GetValue();
      double num2 = Neuron::ActivationDerivativeNeuron_(num);
      double delta = num1 * num2;
      neuron.SetDelta(delta);
    }
  }
  answer.clear();
}

void Perceptron::UpdateWeight(const vector<double> &input_value) { 
  std::vector<double> inputVals = input_value;
  for(int i = 0; i < amount_of_hidden_layers_ + 1; ++i) {
    if (i != 0) {
      for (Neuron neuron : layer_[i - 1]) {
        double neuronTemp = neuron.GetValue();
        inputVals.push_back(neuronTemp);
      }
    }
    for (Neuron neuron : layer_[i]) {
      for (size_t j = 0; j < inputVals.size(); ++j) {
        double num1 = neuron.GetDelta();
        double num2 = inputVals[j];
        double num_mul = kALPHA * num1 * num2;
        if (num_mul != 0.0) {
          std::cout<<"smth";
        }
        neuron.GetWeight(j) -= num_mul;
      }
    }
    inputVals.clear();
  }
}

//  получение значений нейронов на последнем слое
double Perceptron::GetResult(int index_neuron) {
  return layer_.back()[index_neuron].GetValue();
}


double Perceptron::GetError() {
  return average_error_;
}

void Perceptron::LearnProgressOutput(const std::vector<double>& expected) {
  double error_koef = 0.0;
  for (int i = 0; i < layer_.back().size(); ++i)
    error_koef += pow(expected[i] - layer_.back()[i].GetValue(), 2);
  error_koef /= 2;
  std::cout<<"Вывод:\n";
  for (int i = 0; i < layer_.back().size(); ++i)
    std::cout<<layer_.back()[i].GetValue()<<" ";
  std::cout<<"\nОжидаемый рез-т:\n";
  for (int i = 0; i < expected.size(); ++i)
    std::cout<<expected[i]<<" ";
  std::cout<<"\nКоэф. ошибки:\n" << error_koef<<std::endl;
}

//  мне нужен из нейрона
//  GetValue
//  FeedForward
//  constructor (topology, index_l, index_n)