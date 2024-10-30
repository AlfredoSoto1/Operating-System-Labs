#include "task_measurer.h"

#define NUM_TESTS 6
#define NUM_SAMPLES 1
#define NUM_CHILDREN 3

int main() {
  int priorities[NUM_TESTS][NUM_CHILDREN] = {
      {0, 0, 0},  {-10, 0, 10},  {-20, 0, 10},
      {0, 0, 20}, {10, 10, -10}, {-20, -20, -20},
  };

  // Open CSV file for recording results
  FILE* csv = HandleCsv();

  for (int i = 0; i < 1; i++) {
    // Create schedule sample tests
    ScheduleSampleTest test;
    test.samples = NUM_SAMPLES;
    test.children = NUM_CHILDREN;
    test.priorities = priorities[i];

    // Prepare and set the samples
    GenerateSamples(csv, &test);
    FreeSamples(&test);
  }

  // Close the CSV file
  fclose(csv);

  return 0;
}