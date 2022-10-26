#include "../includes/network.h"

s21::Network::Network(std::vector<int> spec, size_t input_size,
size_t num_classes, double learning_rate) : m_learning_rate_(learning_rate) {
  for (size_t i = 0; i < spec.size(); ++i) {
    if (i == 0)
      m_layers_.push_back(new Layer(input_size, spec.at(i)));
    else
      m_layers_.push_back(new Layer(m_layers_.at(i - 1)->GetNeurons().size(), spec.at(i)));
  }
  m_layers_.push_back(new Layer(m_layers_.at(m_layers_.size() - 1)->GetNeurons().size(), num_classes));
}

// ???
s21::Network::~Network() {
  for (size_t i = 0; i < m_layers_.size(); ++i) {
    delete m_layers_[i];
  }
}

double s21::Network::Activate(const std::vector<double>& weights, const std::vector<double>& input) {
  double activation = weights.back();  // bias
  for (size_t i = 0; i < weights.size() - 1; ++i) {
    activation += weights[i] * input[i];
  }
  return activation;
}

double s21::Network::Transfer(double activation_val) {
  return 1.0 / (1.0 + exp(-activation_val));
}

double s21::Network::TransferDerivative(double output) {
  return output * (1.0 - output);
}

std::vector<double> s21::Network::ForwardProp(const std::vector<double>& input_data) {
  std::vector<double> inputs = input_data; // getnormalizedfeaturevector
  for (size_t i = 0; i < m_layers_.size(); ++i) {
    Layer *layer = m_layers_.at(i);
    std::vector<double> new_inputs;
    for (Neuron* n : layer->GetNeurons()) {
      double activation = Activate(n->GetWeights(), inputs);
      n->SetValue(Transfer(activation));
      new_inputs.push_back(n->GetValue());
    }
    inputs = new_inputs;
  }
  return inputs;  // output layer values
}

void s21::Network::BackProp(const std::vector<double>& expected_data) {
  for (size_t i = m_layers_.size() - 1; (int)i >= 0; --i) {
    Layer* layer = m_layers_.at(i);
    std::vector<double> errors;
    if (i != m_layers_.size() - 1) {
      for (size_t j = 0; j < layer->GetNeurons().size(); ++j) {
        double error = 0.0;
        for (Neuron* n : m_layers_.at(i + 1)->GetNeurons()) {
          error += (n->GetWeights().at(j) * n->GetDelta());
        }
        errors.push_back(error);
      }
    } else {
      for (size_t j = 0; j < layer->GetNeurons().size(); ++j) {
        Neuron* n = layer->GetNeurons().at(j);
        errors.push_back(expected_data.at(j) - n->GetValue());  // expected - actual
      }
    }
    for (size_t j = 0; j < layer->GetNeurons().size(); ++j) {
      Neuron* n = layer->GetNeurons().at(j);
      n->SetDelta(errors.at(j) * TransferDerivative(n->GetValue()));  // gradient / derivative part of back prop
    }
  }
}

void s21::Network::UpdateWeights(const std::vector<double>& input_data) {
  std::vector<double> inputs = input_data;
  for (size_t i = 0; i < m_layers_.size(); ++i) {
    if (i != 0) {
      for (Neuron* n : m_layers_.at(i - 1)->GetNeurons()) {
        inputs.push_back(n->GetValue());
      }
    }
    for (Neuron* n : m_layers_.at(i)->GetNeurons()) {
      for (size_t j = 0; j < inputs.size(); ++j) {
        n->GetWeights().at(j) += m_learning_rate_ * n->GetDelta() * inputs.at(j);
      }
      n->GetWeights().back() += m_learning_rate_ * n->GetDelta();
    }
    inputs.clear();
  }
}

int s21::Network::Predict(const std::vector<double>& input_data) {
  std::vector<double> outputs = ForwardProp(input_data);
  return std::distance(outputs.begin(), std::max_element(outputs.begin(), outputs.end()));
}

double s21::Network::LearnOutput(const std::vector<double>& expected) {
  double error = GetOutputError_(expected);
  std::cout<<"\nexpected output:\n";
  std::cout<< std::distance(expected.begin(), std::max_element(expected.begin(), expected.end()));
  std::cout<<"\ncurrent output:\n";
  for (size_t i = 0; i < m_layers_.back()->GetNeurons().size(); ++i) {
    printf("%.3f ", m_layers_.back()->GetNeurons().at(i)->GetValue());
  }
  printf("\ncurrent average err:\n%.4f", error);
  return error;
}

double s21::Network::GetOutputError_(const std::vector<double>& expected) {
  double output_err = 0.0;
  for (size_t i = 0; i < m_layers_.back()->GetNeurons().size(); ++i)
    output_err += pow(expected[i] - m_layers_.back()->GetNeurons()[i]->GetValue(), 2);
  return output_err * 0.5f;
}