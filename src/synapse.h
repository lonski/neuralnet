#ifndef SYNAPSE_H
#define SYNAPSE_H

#include "neuron.h"

namespace nn {

struct Synapse {
  Synapse(Neuron* left, Neuron* right, double weight)
      : left(left), right(right), weight(weight) {}

  Neuron* left;
  Neuron* right;
  double weight;
};

}  // namespace nn

#endif  // SYNAPSE_H
