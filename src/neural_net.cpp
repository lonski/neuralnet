#include "neural_net.h"
#include <cstdlib>
#include <ctime>

NeuralNetwork::NeuralNetwork(Parameters p)
    : m_expectedOutput(p.expectedOutput), m_activationFn(p.activationFn) {
  srand(time(0));
  addLayer(new Layer(p.input));
  for (int i = 0; i < p.hiddenLayerCount; ++i) {
    addLayer(new Layer(std::vector<double>(p.hiddenLayerNeuronsCount, 0.0)));
  }
  addLayer(new Layer(std::vector<double>(p.expectedOutput.size(), 0.0)));
}

NeuralNetwork::~NeuralNetwork() {
  for (Synapse* s : m_synapses) {
    delete s;
  }
  for (Layer* l : m_layers) {
    delete l;
  }
}

void NeuralNetwork::addLayer(Layer* layer) {
  m_layers.push_back(layer);
  if (m_layers.size() > 1) {
    Layer* previousLayer = m_layers[m_layers.size() - 2];
    connectLayers(previousLayer, layer);
  }
}

void NeuralNetwork::learn(int iterationCount) {
  while (iterationCount--) {
    calculateNeuronValues();
    calculateError();
  }
}

void NeuralNetwork::connectLayers(Layer* l1, Layer* l2) {
  for (Neuron* left : l1->neurons) {
    for (Neuron* right : l2->neurons) {
      Synapse* synapse = new Synapse(left, right, getInitialSynapseWeigth());
      m_synapses.push_back(synapse);
    }
  }
}

double NeuralNetwork::getInitialSynapseWeigth() {
  return ((double)rand() / (RAND_MAX));
}

void NeuralNetwork::calculateNeuronValues() {
  Layer* previousLayer = nullptr;
  for (Layer* currentLayer : m_layers) {
    if (previousLayer) {
      for (Neuron* right : currentLayer->neurons) {
        right->data = 0.0;
        for (Neuron* left : previousLayer->neurons) {
          Synapse* synapse = findSynapse(left, right);
          right->data += left->data * synapse->weight;
        }
        right->data = m_activationFn(right->data);
      }
    }
    previousLayer = currentLayer;
  }
}

Synapse* NeuralNetwork::findSynapse(Neuron* left, Neuron* right) {
  for (Synapse* s : m_synapses) {
    if (s->left == left && s->right == right)
      return s;
  }
  return nullptr;
}

void NeuralNetwork::calculateError() {
  Layer* outputLayer = m_layers.back();
  m_error = 0;
  for (size_t i = 0; i < m_expectedOutput.size(); ++i) {
    double target = m_expectedOutput[i];
    double output = outputLayer->neurons[i]->data;
    double diff = target - output;
    m_error += 0.5 * (diff * diff);
  }
}
