#ifndef NEURAL_NET_WRAPPER_H
#define NEURAL_NET_WRAPPER_H

#include "../../src/neural_net.h"

namespace test {

class NeuralNetworkWrapper : public NeuralNetwork {
 public:
  NeuralNetworkWrapper(Parameters p) : NeuralNetwork(p) {}
  const std::vector<Synapse*>& getSynapses() { return m_synapses; }

  bool containsSynapse(Neuron* left, Neuron* right) {
    for (Synapse* s : m_synapses) {
      if (s->left == left && s->right == right)
        return true;
    }
    return false;
  }

  Synapse* findSynapsePub(Neuron* left, Neuron* right) {
    return findSynapse(left, right);
  }

  const std::vector<Layer*>& getLayers() { return m_layers; }

  double getError() { return m_error; }

  void calculateNeuronValuesPub() { calculateNeuronValues(); }
};

}  // namespace test

#endif  // NEURAL_NET_WRAPPER_H
