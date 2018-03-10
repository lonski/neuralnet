#ifndef NEURALNETTEST_H
#define NEURALNETTEST_H

#include "../src/neural_net.h"
#include <cassert>
#include <iostream>

class NeuralNetworkWrapper : public NeuralNetwork {
public:
  const std::vector<Synapse *> &getSynapses() { return m_synapses; }

  bool containsSynapse(Neuron *left, Neuron *right) {
    for (Synapse *s : m_synapses) {
      if (s->left == left && s->right == right)
        return true;
    }
    return false;
  }
};

class NeuralNetTest {
public:
  static void shouldCreateSynapses() {
    Layer *l1 = new Layer({new Neuron(0.1), new Neuron(0.2), new Neuron(0.3)});
    Layer *l2 = new Layer({new Neuron(1.1), new Neuron(1.2)});
    Layer *l3 = new Layer({new Neuron(2.1), new Neuron(2.2), new Neuron(2.3)});

    NeuralNetworkWrapper nn;
    nn.addLayer(l1);
    nn.addLayer(l2);
    nn.addLayer(l3);

    size_t expectedSynapsesCount = 3 * 2 + // synapses between layers l1 <-> l2
                                   2 * 3;  // synapses between layers l2 <-> l3
    assert(nn.getSynapses().size() == expectedSynapsesCount);
  }

  static void shouldConnectLayers() {
    Layer *l1 = new Layer({new Neuron(0.1)});
    Layer *l2 = new Layer({new Neuron(1.1), new Neuron(1.2)});
    Layer *l3 = new Layer({new Neuron(2.1), new Neuron(2.2), new Neuron(2.3)});

    NeuralNetworkWrapper nn;
    nn.addLayer(l1);
    nn.addLayer(l2);
    nn.addLayer(l3);

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
};

#endif
