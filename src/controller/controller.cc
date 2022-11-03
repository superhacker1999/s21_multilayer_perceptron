#include "controller.h"

s21::Controller::Controller(std::string input_path, std::string weights_path)
    : data_handler_(input_path),
    weights_path_(weights_path) {;}

int s21::Controller::getPrediction() {
    s21::Network net({50, 30}, 784, 26, 0.05);
    net.UploadWeightsToNet(net.LoadWeights(weights_path_));
    data_handler_.parseData();
    auto result = data_handler_.GetThisTrainSet(0);
    return net.Predict(result.first);
}
