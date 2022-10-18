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

  // setting input values to the 1st layer
  for (size_t i = 0; i < input_vals.size(); ++i)
    m_layers_[0][i]->SetValue(input_vals[i]);

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
  return new_value;
}

void s21::Net::BackProp(const size_t& answer_pos) {
  std::vector<double> answer(m_layers_.back().size(), 0.0);
  answer[answer_pos - 1] = 1.0;
  
}



void s21::Net::LearnProgressOutput(const std::vector<double>& expected) {
  double err_koef = 0.0;
  for (size_t i = 0; i < m_layers_.back().size(); ++i)
    err_koef += pow(expected[i] - (*m_layers_.back()[i]).GetValue(), 2);
  err_koef /= 200;

  std::cout<<"Output:\n";
  for (size_t i = 0; i < m_layers_.back().size(); ++i)
    std::cout<<(*m_layers_.back()[i]).GetValue()<<" ";

  std::cout<<"\nExpected result:\n";
  for (size_t i = 0; i < expected.size(); ++i)
    std::cout<<expected[i]<<" ";

  printf("\nError koeff: %.3lf %%\n\n", err_koef);
}
