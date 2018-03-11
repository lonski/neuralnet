#ifndef ACTIVATION_FUNCTIONS_TEST_H
#define ACTIVATION_FUNCTIONS_TEST_H

#include <cassert>
#include "../src/activation_functions.h"
#include "util.h"

namespace test {

class ActivationFunctionsTest {
 public:
  /* Test */
  static void logisticFunctionTest() {
    double x = 0.3775;

    double y = ActivationFunctions::LOGISTIC(x);

    assert(areSame(y, 0.5932));
  }

  /* Test */
  static void mulByTwoFunctionTest() {
    double x = 1.0;

    double y = ActivationFunctions::MUL_BY_TWO(x);

    assert(areSame(y, 2));
  }
};

}  // namespace test

#endif  // ACTIVATION_FUNCTIONS_TEST_H
