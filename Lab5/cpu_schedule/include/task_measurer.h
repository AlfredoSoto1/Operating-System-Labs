#ifndef TASK_MEASURER_H
#define TASK_MEASURER_H

#include <stdio.h>

typedef struct {
  int samples;              // Number of samples
  int children;             // Number of children per sample
  int* priorities;          // Priorities assigned for each children.
  double* avrg_time_taken;  // Time taken for each child process in avrg
  long** child_time_taken;  // List of sample times for each child.
} ScheduleSampleTest;

/**
 * @brief Generate new samples for the schedule test given.
 *
 * @param csv
 * @param test
 */
void GenerateSamples(FILE* csv, ScheduleSampleTest* test);

/**
 * @brief Frees any allocated data from the generated sample.
 *
 * @param test
 */
void FreeSamples(ScheduleSampleTest* test);

/**
 * @brief Handles the children spawn sample process.
 *
 * @param test
 * @param sample
 */
void HandleChildrenSample(ScheduleSampleTest* test, int sample);

/**
 * @brief Asigns a heavy loaded cpu task to test process scheduler.
 *
 */
void CpuBoundTask();

/**
 * @brief Creates and prepares a csv with its header
 *
 * @return csv file reference
 */
FILE* HandleCsv();

/**
 * @brief Fills csv file content from sample result test
 *
 * @param csv
 * @param child
 * @param test
 */
void FillCsv(FILE* csv, int child, ScheduleSampleTest* test);

#endif  // TASK_MEASURER_H