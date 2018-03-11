#include <iostream>
#include "activation_functions.h"
#include "neural_net.h"

int main() {
  nn::NeuralNetwork::Parameters params;
  params.input = {0.1, 0.2};
  params.expectedOutput = {0.5, 0.9};
  params.hiddenLayerCount = 1;
  params.hiddenLayerNeuronsCount = 3;
  params.activationFn = nn::ActivationFunctions::LOGISTIC;

  nn::NeuralNetwork* nn = new nn::NeuralNetwork(params);
}
