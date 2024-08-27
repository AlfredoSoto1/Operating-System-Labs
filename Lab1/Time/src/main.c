#include "MyTime.h"

int main() {
  Time time;

  time.hour = 15;
  time.minute = 5;
  time.second = 32;

  PrintTime(&time);

  time = GetTime();

  PrintTime(&time);

  return 0;
}