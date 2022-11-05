#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include "../helpers/datahandler.h"
#include "../includes/network.h"

namespace s21 {
class Controller {
  private:
    std::string weights_path_;
    s21::Network net_;
  
  public:
    Controller(std::string weights_path);
    ~Controller() {};
    int getPredictionFrom(std::vector<int> &input_data);
};
}

#endif  // SRC_CONTROLLER_H_
