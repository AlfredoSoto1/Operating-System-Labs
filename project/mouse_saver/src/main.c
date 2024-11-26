#include "MouseDriver.h"
int main() {
  // Create a new mouse driver attached to the IO device from linux
  InitMouseDriver();

  while (1) {
    GetMouse();
  }

  DisposeMouseDriver();
  return 0;
}