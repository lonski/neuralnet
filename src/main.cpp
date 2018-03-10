#include <iostream>
#include "activation_functions.h"
#include "neural_net.h"

int main() {
  NeuralNetwork::Parameters params;
  params.input = {0.1, 0.2};
  params.expectedOutput = {0.5, 0.9};
  params.hiddenLayerCount = 1;
  params.hiddenLayerNeuronsCount = 3;
  params.activationFn = ActivationFunctions::LOGISTIC;

  NeuralNetwork* nn = new NeuralNetwork(params);
}
