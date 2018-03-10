#ifndef NEURALNETTEST_H
#define NEURALNETTEST_H

#include <cassert>
#include <iostream>
#include "../src/activation_functions.h"
#include "../src/neural_net.h"
#include "util.h"

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

  /* Test */
  static void shouldCalculateNeuronValues() {
    NeuralNetwork::Parameters p = createNuralNetworkParameters();
    p.input = {0.1, 0.2};
    p.expectedOutput = {2.1, 2.2};
    p.activationFn = ActivationFunctions::MUL_BY_TWO;
    NeuralNetworkWrapper nn(p);

    Layer* l1 = nn.getLayers()[0];
    Layer* l2 = nn.getLayers()[1];
    Layer* l3 = nn.getLayers()[2];

    // assert input layer values
    assertFloatEq(l1->neurons[0]->data, 0.1);
    assertFloatEq(l1->neurons[1]->data, 0.2);

    // assert hidden layer values
    float n_1 = l1->neurons[0]->data;
    float n_2 = l1->neurons[1]->data;
    //// first neuron of hidden layer
    float w_11 = nn.findSynapsePub(l1->neurons[0], l2->neurons[0])->weight;
    float w_21 = nn.findSynapsePub(l1->neurons[1], l2->neurons[0])->weight;
    assertFloatEq(l2->neurons[0]->data, (n_1 * w_11 + n_2 * w_21) * 2);
    //// second neuron of hidden layer
    float w_12 = nn.findSynapsePub(l1->neurons[0], l2->neurons[1])->weight;
    float w_22 = nn.findSynapsePub(l1->neurons[1], l2->neurons[1])->weight;
    assertFloatEq(l2->neurons[1]->data, (n_1 * w_12 + n_2 * w_22) * 2);

    // assert output layer values
    n_1 = l2->neurons[0]->data;
    n_2 = l2->neurons[1]->data;
    //// first neuron of hidden layer
    w_11 = nn.findSynapsePub(l2->neurons[0], l3->neurons[0])->weight;
    w_21 = nn.findSynapsePub(l2->neurons[1], l3->neurons[0])->weight;
    assertFloatEq(l3->neurons[0]->data, (n_1 * w_11 + n_2 * w_21) * 2);
    //// second neuron of hidden layer
    w_12 = nn.findSynapsePub(l2->neurons[0], l3->neurons[1])->weight;
    w_22 = nn.findSynapsePub(l2->neurons[1], l3->neurons[1])->weight;
    assertFloatEq(l3->neurons[1]->data, (n_1 * w_12 + n_2 * w_22) * 2);
  }

 private:
  static NeuralNetwork::Parameters createNuralNetworkParameters() {
    NeuralNetwork::Parameters p;
    p.input = {0.1, 0.2, 0.3};
    p.expectedOutput = {2.1, 2.2, 2.3};
    p.hiddenLayerCount = 1;
    p.hiddenLayerNeuronsCount = 2;
    p.activationFn = [](float x) { return x; };
    return p;
  }
};

#endif
