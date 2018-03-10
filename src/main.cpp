#include "neural_net.h"
#include <iostream>

int main() {
  NeuralNetwork *nn = new NeuralNetwork();
  nn->addLayer(new Layer({new Neuron(0.1), new Neuron(0.2)}));
  nn->addLayer(new Layer({new Neuron(1.1), new Neuron(1.2), new Neuron(1.2)}));
  nn->addLayer(new Layer({new Neuron(2.2)}));
}
