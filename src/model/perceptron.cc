//
// Created by Chastity Eryn on 10/14/22.
//

#include "perceptron.h"


using namespace s21;

//  инициализация нейронной сети рандомными весами
//  расстановка размеров
//  остальное происходит в классе нейрона
Perceptron::Perceptron(vector<int> &topology) {
  std::vector<Neuron>* prev_layer = nullptr;
  for (size_t layer_num = 0; layer_num < topology.size(); ++layer_num) {
    layers_.push_back(Layer());
    prev_layer = layer_num == 0 ? nullptr : &(layers_[layer_num - 1]);
    for (int neuron_num = 0; neuron_num < topology[layer_num]; ++neuron_num) {
//  конструктор нейрона, отдаем топологию и индекс текущего слоя
        layers_[layer_num].push_back(Neuron(topology, layer_num, neuron_num));
        layers_[layer_num][neuron_num].ConnectionNeuron(prev_layer);
    }
  }
  std::cout<<this->layers_.size()<<std::endl;
}

//  продвижение вперед по слоям, расстановка значений в нейронах, активайция?
void Perceptron::FeedForward(const vector<double> &input_value) {
  // assert(input_value.size() == 784);
  if (input_value.size() != layers_[0].size())
    throw std::length_error("Error! Wrong size input value");

  //  установка значений первого слоя
  for (size_t i = 0; i < input_value.size(); ++i)
    layers_[0][i].setValue(input_value[i]);

  for (size_t layer_num = 0; layer_num < layers_.size(); ++layer_num) {
    //  сделали вывод, что он не нужен
//    Layer &prev_layer = layers_[layer_num - 1];

    //  продвижение вперед у нейрона
    //  он идет по нейронам предыдущего слоя, *какие-то формулы*
    for (size_t neuron_num = 0; neuron_num < layers_[layer_num].size(); ++neuron_num) {
      printf("\n%p -- %p\n", &layers_[layer_num - 1], layers_[layer_num][neuron_num].previous_layer_);
      layers_[layer_num][neuron_num].FeedForward();
    }
  }
}

void Perceptron::BackPropagation(const int& answer_pos) {
  // Layer &output_layer = layers_.back();
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
  // for (size_t layer_num = layers_.size() - 2; layer_num > 0; --layer_num) {

  // }
  std::vector<double> answer(2, 0);
  answer[answer_pos - 1] = 1.0;
  for (int i = amount_of_hidden_layers_; i >= 0; --i) {
    std::vector<double> errors;
    if (i != amount_of_hidden_layers_) {
      for (size_t j = 0; j < layers_[i + 1].size(); ++j) {
        double error = 0.0;
        for (Neuron neuron : layers_[i + 1]) {
          double temp_error = neuron.GetWeight(j) * neuron.GetDelta();
          error += temp_error;
        }
        errors.push_back(error);
      }
    } else {
      for (size_t j = 0; j < layers_[i].size(); ++j) {
        errors.push_back(layers_[i][j].GetValue() - answer[j]);
      }
    }
    for (size_t j = 0; j < layers_[i].size(); ++j) {
      Neuron neuron = layers_[i][j];
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
      for (Neuron neuron : layers_[i - 1]) {
        double neuronTemp = neuron.GetValue();
        inputVals.push_back(neuronTemp);
      }
    }
    for (Neuron neuron : layers_[i]) {
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
  return layers_.back()[index_neuron].GetValue();
}


double Perceptron::GetError() {
  return average_error_;
}

void Perceptron::LearnProgressOutput(const std::vector<double>& expected) {
  double error_koef = 0.0;
  for (size_t i = 0; i < layers_.back().size(); ++i)
    error_koef += pow(expected[i] - layers_.back()[i].GetValue(), 2);
  error_koef /= 2;
  std::cout<<"Вывод:\n";
  for (size_t i = 0; i < layers_.back().size(); ++i)
    printf("%f ", layers_.back()[i].GetValue());
  std::cout<<"\nОжидаемый рез-т:\n";
  for (size_t i = 0; i < expected.size(); ++i)
    std::cout<<expected[i]<<" ";
  std::cout<<"\nКоэф. ошибки:\n" << error_koef<<std::endl<<std::endl;
}

//  мне нужен из нейрона
//  GetValue
//  FeedForward
//  constructor (topology, index_l, index_n)