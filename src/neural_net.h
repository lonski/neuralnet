#ifndef NEURALNET_H
#define NEURALNET_H

#include <functional>
#include <vector>

struct Neuron {
  Neuron(double data) : data(data) {}
  double data;
};

struct Synapse {
  Synapse(Neuron* left, Neuron* right, double weight)
      : left(left), right(right), weight(weight) {}

  Neuron* left;
  Neuron* right;
  double weight;
};

struct Layer {
  Layer(std::vector<double> neuron_values) {
    for (double neuron_data : neuron_values) {
      neurons.push_back(new Neuron(neuron_data));
    }
  }
  Layer() {}
  ~Layer() {
    for (Neuron* n : neurons) {
      delete n;
    }
  }

  std::vector<Neuron*> neurons;
};

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
};

#endif
