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
    double toleratedError;
  };

  NeuralNetwork(Parameters Parameters);
  ~NeuralNetwork();

  void learn(int iterationCount);
  double getTotalError() const;

 protected:
  std::vector<Layer*> m_layers;
  std::vector<Synapse*> m_synapses;
  std::vector<double> m_expectedOutput;
  std::function<double(double)> m_activationFn;
  double m_totalError;
  double m_toleratedError;

  void addLayer(Layer* layer);
  void connectLayers(Layer* l1, Layer* l2);
  double getInitialSynapseWeigth();

  void calculateError();
  void calculateNeuronValues();
  void recalculateOutputLayerWeigths();
  void recalculateHiddenLayerWeigths();
  void calculateNewWeight(Layer* lastHiddenLayer, Neuron* right);
  void applyNewWeigths();

  Synapse* findSynapse(Neuron* left, Neuron* right);
};

}  // namespace nn

#endif
