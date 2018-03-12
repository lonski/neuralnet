#include "neural_net.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

namespace nn {

NeuralNetwork::NeuralNetwork(Parameters p)
    : m_expectedOutput(p.expectedOutput),
      m_activationFn(p.activationFn),
      m_toleratedError(p.toleratedError) {
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
  for (int i = 0; i < iterationCount; ++i) {
    calculateNeuronValues();
    calculateError();
    std::cout << "\rIteration " << i + 1 << "/" << iterationCount
              << " : error = " << m_totalError;
    if (m_totalError < m_toleratedError) {
      std::cout << std::endl
                << "Total error within limit: " << m_totalError << " < "
                << m_toleratedError;
      break;
    }
    recalculateOutputLayerWeigths();
    recalculateHiddenLayerWeigths();
    applyNewWeigths();
  }
  std::cout << std::endl;
}

double NeuralNetwork::getTotalError() const {
  return m_totalError;
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

void NeuralNetwork::applyNewWeigths() {
  for (Synapse* s : m_synapses)
    s->weight = s->new_weight;
}

void NeuralNetwork::recalculateOutputLayerWeigths() {
  Layer* outputLayer = m_layers[m_layers.size() - 1];
  Layer* leftLayer = m_layers[m_layers.size() - 2];

  for (size_t i = 0; i < outputLayer->neurons.size(); ++i) {
    Neuron* right = outputLayer->neurons[i];
    right->dE_dOut = right->data - m_expectedOutput[i];
    right->dOut_dNet = right->data * (1 - right->data);
    calculateNewWeights(leftLayer, right);
  }
}

void NeuralNetwork::recalculateHiddenLayerWeigths() {
  size_t lastHiddenLayerIdx = m_layers.size() - 2;
  for (size_t layerIdx = lastHiddenLayerIdx; layerIdx > 1; --layerIdx) {
    Layer* currentLayer = m_layers[layerIdx];
    Layer* leftLayer = m_layers[layerIdx - 1];
    Layer* rightLayer = m_layers[layerIdx + 1];

    for (size_t i = 0; i < currentLayer->neurons.size(); ++i) {
      Neuron* current = currentLayer->neurons[i];
      current->dOut_dNet = current->data * (1 - current->data);
      current->dE_dOut = 0.0;
      for (Neuron* right : rightLayer->neurons)
        current->dE_dOut += right->dE_dOut * right->dOut_dNet *
                            findSynapse(current, right)->weight;
      calculateNewWeights(leftLayer, current);
    }
  }
}

void NeuralNetwork::calculateNewWeights(Layer* leftLayer, Neuron* right) {
  for (Neuron* left : leftLayer->neurons) {
    double dNet_dW = left->data;
    double dE_dW = right->dE_dOut * right->dOut_dNet * dNet_dW;
    Synapse* synapse = findSynapse(left, right);
    synapse->new_weight = synapse->weight - 0.5 * dE_dW;
  }
}

Synapse* NeuralNetwork::findSynapse(Neuron* left, Neuron* right) {
  for (Synapse* s : m_synapses)
    if (s->left == left && s->right == right)
      return s;

  return nullptr;
}

}  // namespace nn
