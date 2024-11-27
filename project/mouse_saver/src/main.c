#include "MouseDriver.h"

int main() {
  // initiate screen and drivers
  InitScreenBuffer();
  InitMouseDriver();

  // Listen for IO
  while (1) {
    GetMouse(GetScreen());
  }

  // Free allocated data
  DisposeMouseDriver();
  DisposeScreenBuffer();
  return 0;
}