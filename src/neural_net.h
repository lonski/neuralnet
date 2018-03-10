#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>

struct Neuron {
  Neuron(float data) : data(data) {}
  float data;
};

struct Synapse {
  Synapse(Neuron *left, Neuron *right, float weight)
      : left(left), right(right), weight(weight) {}

  Neuron *left;
  Neuron *right;
  float weight;
};

struct Layer {
  Layer(std::vector<Neuron *> neurons) : neurons(neurons) {}
  Layer() {}
  ~Layer() {
    for (Neuron *n : neurons) {
      delete n;
    }
  }

  std::vector<Neuron *> neurons;
};

class NeuralNetwork {
public:
  NeuralNetwork();
  NeuralNetwork(std::vector<std::vector<float>> topology);
  ~NeuralNetwork();

  void addLayer(Layer *layer);

protected:
  std::vector<Layer *> m_layers;
  std::vector<Synapse *> m_synapses;

private:
  void connectLayers(Layer *l1, Layer *l2);
  float getInitialSynapseWeigth();
};

#endif
