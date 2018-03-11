#undef NDEBUG
#include <iostream>
#include "ut/activation_functions_test.h"
#include "ut/neural_net_test.h"

#define RUN_TEST(FUN)                           \
  std::cout << "Running " << #FUN << std::endl; \
  FUN;

int main() {
  RUN_TEST(test::NeuralNetTest::shouldCreateSynapses());
  RUN_TEST(test::NeuralNetTest::shouldConnectLayers());
  RUN_TEST(test::NeuralNetTest::shouldInitializeSynapseWeight());
  RUN_TEST(test::NeuralNetTest::shouldCreateRequestedAmountOfLayers());
  RUN_TEST(test::NeuralNetTest::shouldCalculateNeuronValues());
  RUN_TEST(test::NeuralNetTest::shouldCalculateError());
  RUN_TEST(test::ActivationFunctionsTest::logisticFunctionTest());
  RUN_TEST(test::ActivationFunctionsTest::mulByTwoFunctionTest());
}
