#ifndef NEURALNET_H
#define NEURALNET_H

#include <functional>
#include <vector>
#include "layer.h"
#include "neuron.h"
#include "synapse.h"

namespace nn {

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

  void learn(int iterationCount);

 protected:
  std::vector<Layer*> m_layers;
  std::vector<Synapse*> m_synapses;
  std::vector<double> m_expectedOutput;
  std::function<double(double)> m_activationFn;
  double m_totalError;

  void addLayer(Layer* layer);
  void connectLayers(Layer* l1, Layer* l2);
  double getInitialSynapseWeigth();

  void calculateError();
  void calculateNeuronValues();
  void recalculateOutputLayerWeigths();

  Synapse* findSynapse(Neuron* left, Neuron* right);
};

}  // namespace nn

#endif
