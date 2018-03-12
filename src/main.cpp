#include <iostream>
#include <limits>
#include <sstream>
#include "activation_functions.h"
#include "console_utils.h"
#include "neural_net.h"

nn::NeuralNetwork::Parameters getExampleParameters() {
  nn::NeuralNetwork::Parameters params;
  params.input = {0.05, 0.1};
  params.expectedOutput = {0.01, 0.99};
  params.hiddenLayerCount = 2;
  params.hiddenLayerNeuronsCount = 3;
  params.activationFn = nn::ActivationFunctions::LOGISTIC;
  return params;
}

int main() {
  std::cout << " :: Neuronomator 6000 ::" << std::endl;

  bool areParametersAccepted = false;
  nn::NeuralNetwork::Parameters params;

  while (!areParametersAccepted) {
    printLine("Menu");
    std::cout << "1. Enter network parameters" << std::endl;
    std::cout << "2. Use example parameter set" << std::endl;
    std::cout << "0. Exit" << std::endl;
    int choose = getNumber<int>("");

    if (choose == 1) {
      printLine("Enter network parameters");
      clear_cin();
      params = promptForParameters();
    } else if (choose == 2) {
      params = getExampleParameters();
    } else {
      return 0;
    }

    printParams(params);
    areParametersAccepted = getBool("Ok?");
    clear_cin();
  }

  int e = getNumber<int>("Enter maximum number of iterations");
  params.toleratedError = getNumber<double>("Enter tolerated error value");
  nn::NeuralNetwork* nn = new nn::NeuralNetwork(params);

  nn->learn(e);

  printLine("Calculated weights");
  nn->printWeights(std::cout);
}
