#ifndef NEURALNET_H
#define NEURALNET_H

#include <functional>
#include <vector>
#include "layer.h"
#include "neuron.h"
#include "synapse.h"

class NeuralNetwork {
 public:
  struct Parameters {
    std::vector<double> input;
    std::vector<double> expectedOutput;
    int hiddenLayerCount;
    int hiddenLayerNeuronsCount;
    std::function<double(double)> activationFn;
  };

  NeuralNetwork(Parameters Parameters);
  ~NeuralNetwork();

  void addLayer(Layer* layer);
  void learn(int iterationCount);

 protected:
  std::vector<double> m_expectedOutput;
  std::vector<Layer*> m_layers;
  std::vector<Synapse*> m_synapses;
  std::function<double(double)> m_activationFn;
  double m_error;

  void connectLayers(Layer* l1, Layer* l2);
  double getInitialSynapseWeigth();
  void calculateNeuronValues();
  Synapse* findSynapse(Neuron* left, Neuron* right);
  void calculateError();
  void recalculateOutputLayerWeigths();
};

#endif
