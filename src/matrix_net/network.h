#ifndef SRC_MATRIX_NET_NET_H_
#define SRC_MATRIX_NET_NET_H_

#include "helpers/s21_matrix.h"

namespace s21 {
namespace matrix {
class Network {
  private:
    std::vector<S21Matrix*> m_layers_;  // вектор указателей на матрицы слоев, в которых хранятся значения
    std::vector<S21Matrix*> m_weigths_;  // вектора указателей на матрицы весов для каждого слоя
    std::vector<double> m_biases_;  // вектор биасов, m_biases_size() = m_layers_.size() - 1
    const double m_alpha_;  // should be 0.00 - 1.00

  public:
    Network(std::vector<int> spec, size_t input_size,
            size_t num_classes, double learning_rate);
    ~Network();
    S21Matrix ForwardProp(const std::vector<double>& input_data);
  
  private:
    void InitializeLayers_(const std::vector<int>& spec, size_t input_size, size_t num_classes);
    void InitializeWeights_();
    void InitializeBiases_();
    double TransferDerivative(double value);
    
};


}  // namespace matrix
}  // namespace s21

#endif  // SRC_MATRIX_NET_NET_H_