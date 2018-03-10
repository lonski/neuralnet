#ifndef UTIL_H
#define UTIL_H

#include <cassert>
#include <cmath>

static bool areSame(float a, float b) {
  return fabs(a - b) < 0.0001;
}
static void assertFloatEq(float a, float b) {
  assert(areSame(a, b));
}

#endif  // UTIL_H
