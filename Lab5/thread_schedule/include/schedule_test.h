#ifndef SCHEDULE_TEST_H
#define SCHEDULE_TEST_H

#include <pthread.h>
#include <sched.h>
#include <stdio.h>

typedef struct {
  int sample;
  int policy;
  int priority;
  int thread_num;
  long elapsed_time;
  pthread_t thread_id;
} ThreadSampleTest;

/**
 * @brief Assign a CPU bound task to test the scheduler
 *
 */
void CpuBoundTask();

/**
 * @brief Runs sample on main thread context
 *
 * @param arg - number of thread sample
 * @return NULL
 */
void* ThreadFunction(void* arg);

/**
 * @brief Spawns a new thread with sample conditions
 *
 * @param test
 */
void SpawnThread(ThreadSampleTest* test);

/**
 * @brief Joins and frees all data related to the test
 *
 * @param test
 */
void JoinSamples(ThreadSampleTest* test);

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
 * @param test
 */
void FillCsv(FILE* csv, ThreadSampleTest* test);

#endif  // SCHEDULE_TEST_H