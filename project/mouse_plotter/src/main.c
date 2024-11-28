#include <stdio.h>

#include "MousePlotter.h"

int main() {
  InitPlotter();

  Draw();

  DisposePlotter();

  return 0;
}