#include <iostream>
#include "activation_functions.h"
#include "neural_net.h"

int main() {
  nn::NeuralNetwork::Parameters params;
  params.input = {0.05, 0.1};
  params.expectedOutput = {0.01, 0.99};
  params.hiddenLayerCount = 2;
  params.hiddenLayerNeuronsCount = 3;
  params.toleratedError = 0.01;
  params.activationFn = nn::ActivationFunctions::LOGISTIC;

  nn::NeuralNetwork* nn = new nn::NeuralNetwork(params);
  nn->learn(1000);
}
