#ifndef SRC_NET_H_
#define SRC_NET_H_

#include <vector>
#include <cassert>
#include "neuron.h"
#include <cmath>
#include <iostream>


namespace s21 {
class Net {
  private:
    short m_amount_of_hidden_layers_;
    double m_error_;
    double m_average_error_;
    // коэфициент скорости обучения
    // может варьироваться
    const double kALPHA = 0.001f;
    // коэфициент для нормализации входящих значений
    // стандартно для нашей задачи равен 255.0
    const double kKoeff = 1.0f;
    std::vector<s21::Layer> m_layers_;

  public:
    Net(const std::vector<short>&);
    ~Net();
    void FeedForward(const std::vector<double>&);
    double GetNewValue(size_t, size_t);
    void BackProp(const size_t&);
    void UpdateWeights(const std::vector<double>&);

    static double Activation(double);
    static double ActivationDerivative(double);

    void LearnProgressOutput(const std::vector<double>&);

  private:
    double GetOutputError_(const std::vector<double>&);

};
}  // namespace s21

#endif  // SRC_NET_H_