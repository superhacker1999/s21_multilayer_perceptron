#ifndef SRC_NEURON_H_
#define SRC_NEURON_H_

#include <vector>
#include <cmath>

namespace s21 {
class Neuron {
  private:
    double m_value_;
    double m_delta_;
    std::vector<double> m_weights_;
    void InitializeWeights_(size_t);

  public:
  // 2?
    Neuron(size_t );
    std::vector<double>& GetWeights() { return m_weights_; }
    void SetValue(double val) { m_value_ = val; }
    double GetValue() { return m_value_; }
    double GetDelta() { return m_delta_; }
    void SetDelta(double delta) { m_delta_ = delta; }
  
};
}

#endif  // SRC_NEURON_H_