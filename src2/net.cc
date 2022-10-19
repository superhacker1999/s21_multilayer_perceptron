#include "net.h"

s21::Net::Net(const std::vector<short>& topology) {
  m_amount_of_hidden_layers_ = topology.size() - 2;
  for (size_t layer_num = 0; layer_num < topology.size(); ++layer_num) {
    m_layers_.push_back(Layer());
    for (short neuron_num = 0; neuron_num < topology[layer_num]; ++neuron_num)
      m_layers_[layer_num].push_back(new Neuron(topology, layer_num, neuron_num));
  }
}

s21::Net::~Net() {
  for (size_t layer_num = 0; layer_num < m_layers_.size(); ++layer_num)
    for (size_t neuron_num = 0; neuron_num < m_layers_[layer_num].size(); ++neuron_num)
      delete m_layers_[layer_num][neuron_num];
}

void s21::Net::FeedForward(const std::vector<double>& input_vals) {
  assert(input_vals.size() == m_layers_[0].size());

  // setting input values to the input layer
  for (size_t i = 0; i < input_vals.size(); ++i)
    m_layers_[0][i]->SetValue(input_vals[i] / kKoeff);

  for (size_t layer_num = 1; layer_num < m_layers_.size(); ++layer_num)
    for (size_t neuron_num = 0; neuron_num < m_layers_[layer_num].size(); ++neuron_num)
      m_layers_[layer_num][neuron_num]->SetValue(GetNewValue(layer_num, neuron_num));
}

double s21::Net::GetNewValue(size_t layer_num, size_t neuron_num) {
  double new_value = 0.0;
  for (size_t i = 0; i < m_layers_[layer_num - 1].size(); ++i) {
    double prev_weight = m_layers_[layer_num - 1][i]->GetWeight()[neuron_num];
    double prev_value = m_layers_[layer_num - 1][i]->GetValue();
    new_value += prev_weight * prev_value;
  }
  return Activation(new_value);
}

double s21::Net::Activation(double x) {
  return 1.0 / (1.0 + exp(-x));
  // return tanh(x);
}

double s21::Net::ActivationDerivative(double x) {
  return x * (1 - x);
  // return atanh(x);
  // return exp(-x)/((1 + exp(-x))*(1 + exp(-x)));
}

void s21::Net::BackProp(const size_t& answer_pos) {
  std::vector<double> answer(m_layers_.back().size(), 0.0);
  answer[answer_pos - 1] = 0.0;
  for (size_t i = m_layers_.size() - 1; (int)i >= 0; --i) {
    std::vector<double> errors;
    if (i != m_layers_.size() - 1) {
      for (size_t j = 0; j < m_layers_[i].size(); ++j) {
        double error = 0.0;
        for (Neuron *n : m_layers_[i + 1]) {
          double weight = n->GetWeight()[j];
          double delta = n->GetDelta();
          error += weight * delta;
        }
        errors.push_back(error);
      }
    } else {
      for (size_t j = 0; j < m_layers_[i].size(); ++j) {
        Neuron* n = m_layers_[i][j];
        double answer_elem = answer[j];
        double value = n->GetValue();
        errors.push_back(answer_elem - value);
      }
    }
    for(size_t j = 0; j < m_layers_[i].size(); ++j) {
      Neuron* n = m_layers_[i][j];
      double error = errors[j];
      double deriv = ActivationDerivative(n->GetValue());
      n->SetDelta(errors[j] * ActivationDerivative(n->GetValue()));
    }
  }
}

void s21::Net::UpdateWeights(const std::vector<double>& input_vals) {
  std::vector<double> tmp_input = input_vals;
  for (size_t i = 0; i < m_layers_.size(); ++i) {
    if (i != 0) {
      for (Neuron* n : m_layers_[i - 1])
        tmp_input.push_back(n->GetValue());
    }
    for (Neuron* n : m_layers_[i]) {
      for (size_t j = 0; j < tmp_input.size(); ++j) {
        double delta = n->GetDelta();
        double tmp_input_elem = tmp_input[j];
        double new_weight = kALPHA * delta * tmp_input_elem;
        n->GetWeight()[j] += new_weight;
      }
      double delta = n->GetDelta();
      n->GetWeight().back() += kALPHA * delta;
    }
    tmp_input.clear();
  }
}

double s21::Net::GetOutputError_(const std::vector<double>& expected) {
  double output_err = 0.0;
  for (size_t i = 0; i < m_layers_.back().size(); ++i)
    output_err += pow(expected[i] - m_layers_.back()[i]->GetValue(), 2);
  return output_err * 0.5f;
}

// tmp method
void s21::Net::LearnProgressOutput(const std::vector<double>& expected) {
  double err_koef = GetOutputError_(expected) / 100;

  std::cout<<"Output:\n";
  for (size_t i = 0; i < m_layers_.back().size(); ++i)
    std::cout<<(*m_layers_.back()[i]).GetValue()<<" ";

  std::cout<<"\nExpected result:\n";
  for (size_t i = 0; i < expected.size(); ++i)
    std::cout<<expected[i]<<" ";

  printf("\nError koeff: %.3lf %%\n\n", err_koef);
}