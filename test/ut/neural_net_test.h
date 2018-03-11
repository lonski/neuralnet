#ifndef NEURALNETTEST_H
#define NEURALNETTEST_H

#include <cassert>
#include <iostream>
#include "../../src/activation_functions.h"
#include "../common/neural_net_wrapper.h"
#include "../common/util.h"

namespace test {

class NeuralNetTest {
 public:
  /* Test */
  static void shouldCreateSynapses() {
    NeuralNetworkWrapper nn(createNeuralNetworkParameters());

    size_t expectedSynapsesCount = 3 * 2 +  // synapses between layers l1 <-> l2
                                   2 * 3;   // synapses between layers l2 <-> l3
    assert(nn.getSynapses().size() == expectedSynapsesCount);
  }

  /* Test */
  static void shouldCreateRequestedAmountOfLayers() {
    nn::NeuralNetwork::Parameters params = createNeuralNetworkParameters();
    params.hiddenLayerCount = 6;

    NeuralNetworkWrapper nn(params);

    assert(nn.getLayers().size() == 6 + 2);
  }

  /* Test */
  static void shouldConnectLayers() {
    NeuralNetworkWrapper nn(createNeuralNetworkParameters());
    nn::Layer* l1 = nn.getLayers()[0];
    nn::Layer* l2 = nn.getLayers()[1];
    nn::Layer* l3 = nn.getLayers()[2];

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
    NeuralNetworkWrapper nn(createNeuralNetworkParameters());

    double sum = 0;
    for (nn::Synapse* s : nn.getSynapses())
      sum += s->weight;

    assert(sum > 0);
  }

  /* Test */
  static void shouldCalculateNeuronValues() {
    nn::NeuralNetwork::Parameters p = createNeuralNetworkParameters();
    p.input = {0.1, 0.2};
    p.expectedOutput = {2.1, 2.2};
    NeuralNetworkWrapper nn(p);
    nn::Layer* l1 = nn.getLayers()[0];
    nn::Layer* l2 = nn.getLayers()[1];
    nn::Layer* l3 = nn.getLayers()[2];

    nn.calculateNeuronValuesPub();

    // assert input layer values
    assert(areSame(l1->neurons[0]->data, 0.1));
    assert(areSame(l1->neurons[1]->data, 0.2));

    // assert hidden layer values
    double n_1 = l1->neurons[0]->data;
    double n_2 = l1->neurons[1]->data;
    //// first neuron of hidden layer
    double w_11 = nn.findSynapsePub(l1->neurons[0], l2->neurons[0])->weight;
    double w_21 = nn.findSynapsePub(l1->neurons[1], l2->neurons[0])->weight;
    assert(areSame(l2->neurons[0]->data, (n_1 * w_11 + n_2 * w_21) * 2));
    //// second neuron of hidden layer
    double w_12 = nn.findSynapsePub(l1->neurons[0], l2->neurons[1])->weight;
    double w_22 = nn.findSynapsePub(l1->neurons[1], l2->neurons[1])->weight;
    assert(areSame(l2->neurons[1]->data, (n_1 * w_12 + n_2 * w_22) * 2));
    // assert output layer values
    n_1 = l2->neurons[0]->data;
    n_2 = l2->neurons[1]->data;
    //// first neuron of hidden layer
    w_11 = nn.findSynapsePub(l2->neurons[0], l3->neurons[0])->weight;
    w_21 = nn.findSynapsePub(l2->neurons[1], l3->neurons[0])->weight;
    assert(areSame(l3->neurons[0]->data, (n_1 * w_11 + n_2 * w_21) * 2));
    //// second neuron of hidden layer
    w_12 = nn.findSynapsePub(l2->neurons[0], l3->neurons[1])->weight;
    w_22 = nn.findSynapsePub(l2->neurons[1], l3->neurons[1])->weight;
    assert(areSame(l3->neurons[1]->data, (n_1 * w_12 + n_2 * w_22) * 2));
  }

  /* Test */
  static void shouldCalculateError() {
    nn::NeuralNetwork::Parameters p = createNeuralNetworkParameters();
    p.input = {0.5, 0.1};
    p.expectedOutput = {0.1, 0.2};
    NeuralNetworkWrapper nn(p);
    nn::Layer* outputLayer = nn.getLayers()[2];

    nn.learn(1);

    double o1 = outputLayer->neurons[0]->data;
    double diff1 = p.expectedOutput[0] - o1;
    double o2 = outputLayer->neurons[1]->data;
    double diff2 = p.expectedOutput[1] - o2;
    double err = 0.5 * (diff1 * diff1) + 0.5 * (diff2 * diff2);

    assert(areSame(nn.getError(), err));
  }

  /* Test */
  static void shouldImproveError() {
    nn::NeuralNetwork::Parameters params;
    params.input = {0.05, 0.1};
    params.expectedOutput = {0.01, 0.99};
    params.hiddenLayerCount = 2;
    params.hiddenLayerNeuronsCount = 3;
    params.toleratedError = 0.001;
    params.activationFn = nn::ActivationFunctions::LOGISTIC;
    nn::NeuralNetwork* nn = new nn::NeuralNetwork(params);

    nn->learn(1);
    double initError = nn->getTotalError();
    nn->learn(100);
    double outError = nn->getTotalError();

    assert(outError < initError);
  }

 private:
  static nn::NeuralNetwork::Parameters createNeuralNetworkParameters() {
    nn::NeuralNetwork::Parameters p;
    p.input = {0.1, 0.2, 0.3};
    p.expectedOutput = {2.1, 2.2, 2.3};
    p.hiddenLayerCount = 1;
    p.hiddenLayerNeuronsCount = 2;
    p.activationFn = nn::ActivationFunctions::MUL_BY_TWO;
    return p;
  }
};

}  // namespace test

#endif
