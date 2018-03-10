#undef NDEBUG
#include "neural_net_test.h"
#include <iostream>

int main() {
  std::cout << "Running NeuralNetTest::shouldCreateSynapses\n";
  NeuralNetTest::shouldCreateSynapses();
  std::cout << "Running NeuralNetTest::shouldConnectLayers\n";
  NeuralNetTest::shouldConnectLayers();
  std::cout << "Running NeuralNetTest::shouldInitializeSynapseWeight\n";
  NeuralNetTest::shouldInitializeSynapseWeight();
}
