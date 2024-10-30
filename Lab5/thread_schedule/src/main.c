#include "schedule_test.h"

#define SAMPLES 6
#define THREAD_NUM 4

int main() {
  // Set priority tests
  int priority_tests[THREAD_NUM][SAMPLES] = {
      {50, 0, 99, 90, 20, 80},
      {50, 0, 99, 10, 20, 80},
      {50, 99, 0, 90, 80, 20},
      {50, 99, 0, 10, 80, 20},
  };

  // Prepare samples
  ThreadSampleTest test[THREAD_NUM][SAMPLES];

  // Initialize CSV file with headers
  FILE* csv = HandleCsv();

  // Spawn thread samples
  for (int j = 0; j < SAMPLES; j++) {
    for (int i = 0; i < THREAD_NUM; i++) {
      test[i][j].sample = j;
      test[i][j].elapsed_time = 0;
      test[i][j].policy = i < THREAD_NUM / 2 ? SCHED_FIFO : SCHED_RR;
      test[i][j].priority = priority_tests[i][j];
      test[i][j].thread_num = i + 1;

      SpawnThread(&test[i][j]);
    }
  }

  // Query results from samples
  for (int j = 0; j < SAMPLES; j++) {
    for (int i = 0; i < THREAD_NUM; i++) {
      JoinSamples(&test[i][j]);
      FillCsv(csv, &test[i][j]);
    }
  }

  // Close file after filling csv
  fclose(csv);

  return 0;
}