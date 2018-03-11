#include <iostream>
#include <limits>
#include <sstream>
#include "activation_functions.h"
#include "console_utils.h"
#include "neural_net.h"

using namespace std;

int main() {
  bool areParametersAccepted = false;
  nn::NeuralNetwork::Parameters params;
  std::cout << " :: Neuronomator 6000 ::" << std::endl;

  while (!areParametersAccepted) {
    std::cout << "--------------------------------------------------\n";
    params.input = getVector<double>("Enter neuron values of input layer");
    params.expectedOutput =
        getVector<double>("Enter expected neuron values of output layer");
    params.hiddenLayerCount = getNumber<int>("Enter number of hidden layers");
    params.hiddenLayerNeuronsCount =
        getNumber<int>("Enter amount of neurons in hidden layers");
    params.toleratedError = getNumber<double>("Enter tolerated error value");
    params.activationFn = nn::ActivationFunctions::LOGISTIC;

    printParams(params);

    areParametersAccepted = getBool("Ok?");
    clear_cin();
  }

  int e = getNumber<int>("Enter maximum number of iterations");
  nn::NeuralNetwork* nn = new nn::NeuralNetwork(params);
  nn->learn(e);
}
