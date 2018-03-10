#ifndef ACTIVATION_FUNCTIONS_TEST_H
#define ACTIVATION_FUNCTIONS_TEST_H

#include "util.h"
#include "../src/activation_functions.h"

class ActivationFunctionsTest {
public:
  /* Test */
  static void logisticFunctionTest() {
    double x = 0.3775;

    double y = ActivationFunctions::LOGISTIC(x);

    assertDoubleEq(y, 0.5932);
  }

  /* Test */
  static void mulByTwoFunctionTest() {
    double x = 1.0;

    double y = ActivationFunctions::MUL_BY_TWO(x);

    assertDoubleEq(y, 2);
  }
};

#endif // ACTIVATION_FUNCTIONS_TEST_H
