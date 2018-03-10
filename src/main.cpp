#include "neural_net.h"
#include <iostream>

int main() {
  NeuralNetwork::Parameters params;
  params.input = {0.1, 0.2};
  params.expectedOutput = {0.5, 0.9};
  params.hiddenLayerCount = 1;
  params.hiddenLayerNeuronsCount = 3;

  NeuralNetwork *nn = new NeuralNetwork(params);
}
