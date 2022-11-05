#include "controller.h"

s21::Controller::Controller(std::string weights_path) :
    weights_path_(weights_path),
    net_({50, 30}, 784, 26, 0.05) {;}

int s21::Controller::getPredictionFrom(std::vector<int> &input_data) {
    s21::Network net({50, 30}, 784, 26, 0.05);
    s21::DataHandler letters_data(input_data);
    net.UploadWeightsToNet(net.LoadWeights(weights_path_));
    auto result = letters_data.normalizeInput();
    return net.Predict(result);
}
