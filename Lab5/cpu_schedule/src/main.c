#include "task_measurer.h"

#define NUM_TESTS 6
#define NUM_SAMPLES 30
#define NUM_CHILDREN 3

int main() {
  int priorities[NUM_TESTS][NUM_CHILDREN] = {
      {0, 0, 0},  {-10, 0, 10},  {-20, 0, 10},
      {0, 0, 20}, {10, 10, -10}, {-20, -20, -20},
  };

  for (int i = 0; i < NUM_TESTS; i++) {
    // Create schedule sample tests
    ScheduleSampleTest test;
    test.samples = NUM_SAMPLES;
    test.children = NUM_CHILDREN;
    test.priorities = priorities[i];

    // Prepare and set the samples
    GenerateSamples(&test);
    FreeSamples(&test);
  }

  return 0;
}