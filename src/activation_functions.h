#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H

#include <cmath>
#include <functional>

struct ActivationFunctions {
  static const std::function<float(float)> LOGISTIC;
  static const std::function<float(float)> MUL_BY_TWO;
};

const std::function<float(float)> ActivationFunctions::LOGISTIC =
    [](float x) -> float { return 1.0 / (1.0 + exp(-1.0 * x)); };

const std::function<float(float)> ActivationFunctions::MUL_BY_TWO =
    [](float x) -> float { return x * 2; };

#endif  // ACTIVATION_FUNCTIONS_H
