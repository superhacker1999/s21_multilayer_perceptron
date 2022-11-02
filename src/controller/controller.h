#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include "../helpers/datahandler.h"
#include "../includes/network.h"

namespace s21 {
class Controller {
  private:
    s21::DataHandler data_handler_;
    std::string weights_path_;
  
  public:
    Controller();
    Controller(std::string input_path, std::string weights_path);
    ~Controller() {};
    int getPrediction();
};
}

#endif  // SRC_CONTROLLER_H_