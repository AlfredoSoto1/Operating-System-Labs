#include "SqrtFunction.h"

double SqrtFunction(double number) {
  double guess = number / 2.0;
  // Iterate over the function iteratively over 10 terms.
  for (int i = 0; i < 10; i++) {
    guess = 0.5 * (guess + number / guess);
  }
  return guess;
}