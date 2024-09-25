#include "MyTime.h"

#include <time.h>

MyTime CurrentTimeMillis() {
  struct timespec ts;

  clock_gettime(CLOCK_MONOTONIC, &ts);

  return (long long)(ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}