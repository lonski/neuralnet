#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <iostream>
#include <vector>
#include <iomanip>
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
  std::cout << msg << " [t/n]\n>";
  std::string s;
  std::cin >> s;
  return s == "t";
}

void printParams(nn::NeuralNetwork::Parameters params) {
  // calculate the row count
  size_t rows =
      std::max((size_t)(params.hiddenLayerNeuronsCount),
               std::max(params.input.size(), params.expectedOutput.size())) +
      1;

  // calculate row skip for each layer type, to put them in the middle
  size_t iRowSkip = std::max((size_t)0, (rows - params.input.size()) / 2);
  size_t hRowSkip =
      std::max((size_t)0, (rows - params.hiddenLayerNeuronsCount) / 2);
  size_t oRowSkip =
      std::max((size_t)0, (rows - params.expectedOutput.size()) / 2);

  std::cout << std::endl;
  // print each row
  for (size_t i = 0; i < rows; ++i) {
    // print input layer
    if (i == 0) {
      std::cout << " Input    ";
    } else {
      if (i >= iRowSkip && (i - iRowSkip) < params.input.size()) {
        std::cout << "|" << std::setw(6) << std::left << std::setfill('0')
                  << params.input[i - iRowSkip] << "|  ";
      } else {
        std::cout << "          ";
      }
    }

    // print hidden layers
    if (i == 0) {
      for (int h = 0; h < params.hiddenLayerCount; ++h)
        std::cout << "H" << std::setw(2) << std::setfill('0') << h << "  ";
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
        std::cout << "|" << std::setw(6) << std::left << std::setfill('0')
                  << params.expectedOutput[i - oRowSkip] << "|";
      } else {
        std::cout << "        ";
      }
    }

    std::cout << std::endl;
  }
}

#endif
