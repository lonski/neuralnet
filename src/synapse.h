#ifndef SYNAPSE_H
#define SYNAPSE_H

#include "neuron.h"

struct Synapse {
  Synapse(Neuron* left, Neuron* right, double weight)
      : left(left), right(right), weight(weight) {}

  Neuron* left;
  Neuron* right;
  double weight;
};

#endif // SYNAPSE_H
