#undef NDEBUG
#include <iostream>
#include "activation_functions_test.h"
#include "neural_net_test.h"

#define RUN_TEST(FUN)                           \
  std::cout << "Running " << #FUN << std::endl; \
  FUN;

int main() {
  RUN_TEST(NeuralNetTest::shouldCreateSynapses());
  RUN_TEST(NeuralNetTest::shouldConnectLayers());
  RUN_TEST(NeuralNetTest::shouldInitializeSynapseWeight());
  RUN_TEST(NeuralNetTest::shouldCreateRequestedAmountOfLayers());
  RUN_TEST(NeuralNetTest::shouldCalculateNeuronValues());
  RUN_TEST(NeuralNetTest::shouldCalculateError());
  RUN_TEST(ActivationFunctionsTest::logisticFunctionTest());
  RUN_TEST(ActivationFunctionsTest::mulByTwoFunctionTest());
}
