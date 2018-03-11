#ifndef UTIL_H
#define UTIL_H

#include <cmath>

namespace test {

static bool areSame(double a, double b) {
  return fabs(a - b) < 0.0001;
}

}  // namespace test

#endif  // UTIL_H
