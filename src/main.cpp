#include "neural_net.h"
#include <iostream>
#include <random>

int main() {
  NeuralNetwork *nn = new NeuralNetwork({
      {0.1, 0.2},      // input layer
      {1.1, 1.2, 1.3}, // hidden layer
      {2.2}            // output layer
  });
}
