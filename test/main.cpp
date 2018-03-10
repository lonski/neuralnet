#undef NDEBUG
#include <iostream>
#include "neural_net_test.h"

int main() {
  std::cout << "Running NeuralNetTest::shouldCreateSynapses\n";
  NeuralNetTest::shouldCreateSynapses();
  std::cout << "Running NeuralNetTest::shouldConnectLayers\n";
  NeuralNetTest::shouldConnectLayers();
  std::cout << "Running NeuralNetTest::shouldInitializeSynapseWeight\n";
  NeuralNetTest::shouldInitializeSynapseWeight();
  std::cout << "Running NeuralNetTest::shouldCreateRequestedAmountOfLayers\n";
  NeuralNetTest::shouldCreateRequestedAmountOfLayers();
  std::cout << "Running NeuralNetTest::shouldCalculateNeuronValues\n";
  NeuralNetTest::shouldCalculateNeuronValues();
}
