#ifndef SRC_LAYER_H_
#define SRC_LAYER_H_

#include "neuron.h"
#include <vector>

namespace s21 {
class Layer {
  private:
    size_t m_current_layer_size_;
    std::vector<Neuron*> m_neurons_;
    std::vector<double> m_layer_outputs_;
  
  public:
    Layer(size_t, size_t);
    std::vector<Neuron*>& GetNeurons() { return  m_neurons_; }
    

};
}

#endif  // SRC_LAYER_H_