#ifndef NEURAL_NET_WRAPPER_H
#define NEURAL_NET_WRAPPER_H

#include "../../src/neural_net.h"

namespace test {

class NeuralNetworkWrapper : public nn::NeuralNetwork {
 public:
  NeuralNetworkWrapper(nn::NeuralNetwork::Parameters p)
      : nn::NeuralNetwork(p) {}
  const std::vector<nn::Synapse*>& getSynapses() { return m_synapses; }

  bool containsSynapse(nn::Neuron* left, nn::Neuron* right) {
    for (nn::Synapse* s : m_synapses) {
      if (s->left == left && s->right == right)
        return true;
    }
    return false;
  }

  nn::Synapse* findSynapsePub(nn::Neuron* left, nn::Neuron* right) {
    return findSynapse(left, right);
  }

  const std::vector<nn::Layer*>& getLayers() { return m_layers; }

  double getError() { return m_totalError; }

  void calculateNeuronValuesPub() { calculateNeuronValues(); }
};

}  // namespace test

#endif  // NEURAL_NET_WRAPPER_H
