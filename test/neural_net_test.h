#ifndef NEURALNETTEST_H
#define NEURALNETTEST_H

#include <cassert>
#include <iostream>
#include "../src/neural_net.h"

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

  const std::vector<Layer*>& getLayers() { return m_layers; }
};

class NeuralNetTest {
 public:
  /* Test */
  static void shouldCreateSynapses() {
    NeuralNetworkWrapper nn(createNuralNetworkParameters());

    size_t expectedSynapsesCount = 3 * 2 +  // synapses between layers l1 <-> l2
                                   2 * 3;   // synapses between layers l2 <-> l3
    assert(nn.getSynapses().size() == expectedSynapsesCount);
  }

  /* Test */
  static void shouldCreateRequestedAmountOfLayers() {
    NeuralNetwork::Parameters params = createNuralNetworkParameters();
    params.hiddenLayerCount = 6;

    NeuralNetworkWrapper nn(params);

    assert(nn.getLayers().size() == 6 + 2);
  }

  /* Test */
  static void shouldConnectLayers() {
    NeuralNetworkWrapper nn(createNuralNetworkParameters());
    Layer* l1 = nn.getLayers()[0];
    Layer* l2 = nn.getLayers()[1];
    Layer* l3 = nn.getLayers()[2];

    // l1-l2 synapses
    assert(nn.containsSynapse(l1->neurons[0], l2->neurons[0]));
    assert(nn.containsSynapse(l1->neurons[0], l2->neurons[1]));
    // l2-l3 synapses
    assert(nn.containsSynapse(l2->neurons[0], l3->neurons[0]));
    assert(nn.containsSynapse(l2->neurons[0], l3->neurons[1]));
    assert(nn.containsSynapse(l2->neurons[0], l3->neurons[2]));
    assert(nn.containsSynapse(l2->neurons[1], l3->neurons[0]));
    assert(nn.containsSynapse(l2->neurons[1], l3->neurons[1]));
    assert(nn.containsSynapse(l2->neurons[1], l3->neurons[2]));
  }

  /* Test */
  static void shouldInitializeSynapseWeight() {
    NeuralNetworkWrapper nn(createNuralNetworkParameters());

    float sum = 0;
    for (Synapse* s : nn.getSynapses()) {
      sum += s->weight;
      // std::cout << s->weight << " ";
    }

    assert(sum > 0);
  }

 private:
  static NeuralNetwork::Parameters createNuralNetworkParameters() {
    NeuralNetwork::Parameters p;
    p.input = {0.1, 0.2, 0.3};
    p.expectedOutput = {2.1, 2.2, 2.3};
    p.hiddenLayerCount = 1;
    p.hiddenLayerNeuronsCount = 2;
    return p;
  }
};

#endif
