#ifndef NEURON_H
#define NEURON_H

namespace nn {

struct Neuron {
  Neuron(double data) : data(data), dE_dOut(0.0), dOut_dNet(0.0) {}

  double data;
  double dE_dOut;
  double dOut_dNet;
};

}  // namespace nn

#endif  // NEURON_H
