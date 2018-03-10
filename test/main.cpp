#undef NDEBUG
#include <iostream>
#include <cassert>
#include "neural_net_test.h"

int main() {
  std::cout << "Running NeuralNetTest::shouldCreateSynapses\n";
  NeuralNetTest::shouldCreateSynapses();
  std::cout << "Running NeuralNetTest::shouldConnectLayers\n";
  NeuralNetTest::shouldConnectLayers();
}
