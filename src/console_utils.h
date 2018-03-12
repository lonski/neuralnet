#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <iomanip>
#include <iostream>
#include <vector>
#include "neural_net.h"

void clear_cin() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
T getNumber(const std::string& msg) {
  std::cout << msg << "\n>";
  T val;
  while (!(std::cin >> val)) {
    clear_cin();
    std::cout << "Invalid input. Try again.\n>";
  }
  return val;
}

template <typename T>
std::vector<T> getVector(const std::string& msg) {
  std::string line;

  std::cout << msg << " (enter numbers separated with spaces)\n>";
  std::getline(std::cin, line);

  T number;
  std::vector<T> numbers;
  std::istringstream stream(line);
  while (stream >> number)
    numbers.push_back(number);

  return numbers;
}

bool getBool(const std::string& msg) {
  std::cout << msg << " [y/n]\n>";
  std::string s;
  std::cin >> s;
  return s == "y";
}

void printLine(const std::string& message) {
  std::cout << "-----" << std::setw(75) << std::setfill('-') << std::left
            << message << std::endl;
}

nn::NeuralNetwork::Parameters promptForParameters() {
  nn::NeuralNetwork::Parameters params;
  params.input = getVector<double>("Enter neuron values of input layer");
  params.expectedOutput =
      getVector<double>("Enter expected neuron values of output layer");
  params.hiddenLayerCount = getNumber<int>("Enter number of hidden layers");
  params.hiddenLayerNeuronsCount =
      getNumber<int>("Enter amount of neurons in hidden layers");
  params.activationFn = nn::ActivationFunctions::LOGISTIC;

  return params;
}

void printParams(nn::NeuralNetwork::Parameters params) {
  // calculate the row count
  size_t rows =
      std::max((size_t)(params.hiddenLayerNeuronsCount),
               std::max(params.input.size(), params.expectedOutput.size())) +
      1;

  std::cout << "Rows " << rows;

  // calculate row skip for each layer type, to put them in the middle
  size_t iRowSkip = std::max((size_t)0, (rows - params.input.size()) / 2) + 1;
  size_t hRowSkip =
      std::max((size_t)0, (rows - params.hiddenLayerNeuronsCount) / 2) + 1;
  size_t oRowSkip =
      std::max((size_t)0, (rows - params.expectedOutput.size()) / 2) + 1;

  std::cout << std::endl;
  // print each row
  for (size_t i = 0; i < rows; ++i) {
    // print input layer
    if (i == 0) {
      std::cout << " Input    ";
    } else {
      if (i >= iRowSkip && (i - iRowSkip) < params.input.size()) {
        std::cout << "|" << std::setw(6) << std::left << std::setfill(' ')
                  << params.input[i - iRowSkip] << "|  ";
      } else {
        std::cout << "          ";
      }
    }

    // print hidden layers
    if (i == 0) {
      for (int h = 0; h < params.hiddenLayerCount; ++h)
        std::cout << "H" << std::setw(2) << std::right << std::setfill('0') << h
                  << "  ";
    } else {
      std::string hlSymbol =
          (i >= hRowSkip &&
           (i - hRowSkip) < (size_t)params.hiddenLayerNeuronsCount)
              ? "|o|  "
              : "     ";
      for (int h = 0; h < params.hiddenLayerCount; ++h)
        std::cout << hlSymbol;
    }

    // print output layers
    if (i == 0) {
      std::cout << " Output ";
    } else {
      if (i >= oRowSkip && (i - oRowSkip) < params.expectedOutput.size()) {
        std::cout << "|" << std::setw(6) << std::left << std::setfill(' ')
                  << params.expectedOutput[i - oRowSkip] << "|";
      } else {
        std::cout << "        ";
      }
    }

    std::cout << std::endl;
  }
}

#endif
