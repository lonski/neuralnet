#include <iostream>
#include <limits>
#include <sstream>
#include "activation_functions.h"
#include "neural_net.h"
#include "console_utils.h"

using namespace std;

int main() {
  bool areParametersAccepted = false;
  nn::NeuralNetwork::Parameters params;
  std::cout << " :: Neuronomator 6000 ::" << std::endl;
  
  while(!areParametersAccepted) {
    std::cout << "--------------------------------------------------" << std::endl;
    params.input = getVector<double>("Podaj wartości neuronów w warstwie wejściowej");
    params.expectedOutput = getVector<double>("Podaj spodziewane wartości neuronów w warstwie wyjściowej");
    params.hiddenLayerCount = getNumber<int>("Podaj liczbe warstw ukrytych");
    params.hiddenLayerNeuronsCount = getNumber<int>("Podaj liczbe neuronow w warstwach ukrytych");
    params.toleratedError = getNumber<double>("Podaj wartosc bledu granicznego");
    params.activationFn = nn::ActivationFunctions::LOGISTIC;
        
    //print parameters
    //  -> możnaby narysowac siec w ascii :-D
    //     IN  | H1 | H2 | OUT
    //   ---------------------
    //          |x|  |x|
    //   |0.1|  |x|  |x|  |0.05|
    //   |0.3|  |x|  |x|  |0.99|
    //          |x|  |x|
    
    areParametersAccepted = getBool("Ok?");
    clear_cin();
  }
  
  int e = getNumber<int>("Okresl maksymalna liczbe epok");
  nn::NeuralNetwork* nn = new nn::NeuralNetwork(params);
  nn->learn(e);
}

// moźnaby jeszcze dodać printowanie tych parametrów i zapytać usera czy 'ok', a jak nie to powtórzyć cały proces wczytywania