#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H

#include <cmath>
#include <functional>

struct ActivationFunctions {
  static const std::function<double(double)> LOGISTIC;
  static const std::function<double(double)> MUL_BY_TWO;
};

const std::function<double(double)> ActivationFunctions::LOGISTIC =
    [](double x) -> double { return 1.0 / (1.0 + exp(-1.0 * x)); };

const std::function<double(double)> ActivationFunctions::MUL_BY_TWO =
    [](double x) -> double { return x * 2; };

#endif  // ACTIVATION_FUNCTIONS_H
