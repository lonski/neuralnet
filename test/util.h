#ifndef UTIL_H
#define UTIL_H

#include <cassert>
#include <cmath>

static bool areSame(double a, double b) {
  return fabs(a - b) < 0.0001;
}
static void assertDoubleEq(double a, double b) {
  assert(areSame(a, b));
}

#endif  // UTIL_H
