#ifndef SRC_NEURON_H_
#define SRC_NEURON_H_

#include <vector>
#include <random>
#include <cmath>

namespace s21 {
  class Neuron;
  using Layer = std::vector<s21::Neuron*>;
}

namespace s21 {
class Neuron {
  private:
    size_t m_index_;
    double m_value_;
    double m_delta_;
    std::vector<double> m_weight_;

  public:
    Neuron(const std::vector<short>&, size_t, size_t);
    ~Neuron() {
      ;
    }
    void SetValue(const double& value) { m_value_ = ActivationNeuron_(value); }
    double GetValue() const { return m_value_; }
    std::vector<double>& GetWeight() { return m_weight_; }

  private:
    double RandomWeightGenerate_();
    double ActivationNeuron_(double);
};
}  // namespace s21

#endif  // SRC_NEURON_H_