#include "MouseDriver.h"

int main() {
  // initiate screen and drivers
  InitMouseDriver();

  // Listen for IO
  while (1) {
    GetMouse();
  }

  // Free allocated data
  DisposeMouseDriver();
  return 0;
}