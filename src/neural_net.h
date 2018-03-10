#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>

struct Neuron {
  Neuron(float data) : data(data) {}
  float data;
};

struct Synapse {
  Synapse(Neuron* left, Neuron* right, float weight)
      : left(left), right(right), weight(weight) {}

  Neuron* left;
  Neuron* right;
  float weight;
};

struct Layer {
  Layer(std::vector<float> neuron_values) {
    for (float neuron_data : neuron_values) {
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
    std::vector<float> input;
    std::vector<float> expectedOutput;
    int hiddenLayerCount;
    int hiddenLayerNeuronsCount;
  };

  NeuralNetwork(Parameters Parameters);
  ~NeuralNetwork();

  void addLayer(Layer* layer);

 protected:
  std::vector<float> m_expectedOutput;
  std::vector<Layer*> m_layers;
  std::vector<Synapse*> m_synapses;

  void connectLayers(Layer* l1, Layer* l2);
  float getInitialSynapseWeigth();
  void calculateNeuronValues();
  Synapse* findSynapse(Neuron* left, Neuron* right);
};

#endif
