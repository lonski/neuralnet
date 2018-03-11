#include "neural_net.h"
#include <cstdlib>
#include <ctime>

NeuralNetwork::NeuralNetwork(Parameters p)
    : m_expectedOutput(p.expectedOutput), m_activationFn(p.activationFn) {
  srand(time(0));
  addLayer(new Layer(p.input));
  for (int i = 0; i < p.hiddenLayerCount; ++i)
    addLayer(new Layer(p.hiddenLayerNeuronsCount));
  addLayer(new Layer(p.expectedOutput.size()));
}

NeuralNetwork::~NeuralNetwork() {
  for (Synapse* s : m_synapses)
    delete s;
  for (Layer* l : m_layers)
    delete l;
}

void NeuralNetwork::addLayer(Layer* layer) {
  m_layers.push_back(layer);
  if (m_layers.size() > 1) {
    Layer* previousLayer = m_layers[m_layers.size() - 2];
    connectLayers(previousLayer, layer);
  }
}

void NeuralNetwork::connectLayers(Layer* l1, Layer* l2) {
  for (Neuron* left : l1->neurons)
    for (Neuron* right : l2->neurons)
      m_synapses.push_back(new Synapse(left, right, getInitialSynapseWeigth()));
}

double NeuralNetwork::getInitialSynapseWeigth() {
  return (double)rand() / RAND_MAX;
}

void NeuralNetwork::learn(int iterationCount) {
  while (iterationCount--) {
    calculateNeuronValues();
    calculateError();
    recalculateOutputLayerWeigths();
  }
}

void NeuralNetwork::calculateNeuronValues() {
  Layer* previousLayer = nullptr;
  for (Layer* currentLayer : m_layers) {
    if (previousLayer) {
      for (Neuron* right : currentLayer->neurons) {
        right->data = 0.0;
        for (Neuron* left : previousLayer->neurons)
          right->data += left->data * findSynapse(left, right)->weight;
        right->data = m_activationFn(right->data);
      }
    }
    previousLayer = currentLayer;
  }
}

void NeuralNetwork::calculateError() {
  Layer* outputLayer = m_layers.back();
  m_totalError = 0;
  for (size_t i = 0; i < m_expectedOutput.size(); ++i) {
    double target = m_expectedOutput[i];
    double output = outputLayer->neurons[i]->data;
    double diff = target - output;
    m_totalError += 0.5 * (diff * diff);
  }
}

void NeuralNetwork::recalculateOutputLayerWeigths() {
  Layer* outputLayer = m_layers[m_layers.size() - 1];
  Layer* lastHiddenLayer = m_layers[m_layers.size() - 2];

  for (size_t i = 0; i < outputLayer->neurons.size(); ++i) {
    Neuron* right = outputLayer->neurons[i];
    double out = right->data;
    double target = m_expectedOutput[i];

    for (Neuron* left : lastHiddenLayer->neurons) {
      double dE_dOut = out - target;
      double dOut_dNet = out * (1 - out);
      double dNet_dW = left->data;
      double dE_dW = dE_dOut * dOut_dNet * dNet_dW;
      Synapse* synapse = findSynapse(left, right);
      synapse->weight = synapse->weight - 0.5 * dE_dW;
    }
  }
}

Synapse* NeuralNetwork::findSynapse(Neuron* left, Neuron* right) {
  for (Synapse* s : m_synapses)
    if (s->left == left && s->right == right)
      return s;

  return nullptr;
}
