#ifndef ACTIVATION_FUNCTIONS_TEST_H
#define ACTIVATION_FUNCTIONS_TEST_H

#include "util.h"
#include "../src/activation_functions.h"

class ActivationFunctionsTest {
public:
  /* Test */
  static void logisticFunctionTest() {
    float x = 0.3775;

    float y = ActivationFunctions::LOGISTIC(x);

    assertFloatEq(y, 0.5932);
  }

  /* Test */
  static void mulByTwoFunctionTest() {
    float x = 1.0;

    float y = ActivationFunctions::MUL_BY_TWO(x);

    assertFloatEq(y, 2);
  }
};

#endif // ACTIVATION_FUNCTIONS_TEST_H
