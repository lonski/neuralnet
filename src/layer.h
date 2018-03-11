#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include "neuron.h"

struct Layer {
  Layer(std::vector<double> neuron_values) {
    for (double neuron_data : neuron_values) {
      neurons.push_back(new Neuron(neuron_data));
    }
  }
  Layer() {}
  ~Layer() {
    for (Neuron* n : neurons) {
      delete n;
    }
  }

  std::vector<Neuron*> neurons;
};

#endif // LAYER_H
