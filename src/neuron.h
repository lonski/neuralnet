#ifndef NEURON_H
#define NEURON_H

namespace nn {

struct Neuron {
  Neuron(double data) : data(data) {}

  double data;
};

}  // namespace nn

#endif  // NEURON_H
