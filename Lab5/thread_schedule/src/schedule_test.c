#include "schedule_test.h"

#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

void CpuBoundTask() {
  // Make CPU run at max
  int i = 0;
  while (i < 200) {
    for (volatile long j = 0; j < 1000000000; j++);
    i++;
  }
}

void* ThreadFunction(void* arg) {
  ThreadSampleTest* test = (ThreadSampleTest*)arg;

  int policy;
  struct sched_param param;
  pthread_getschedparam(pthread_self(), &policy, &param);

  // Obtain the current thread's policy
  const char* policy_str = (policy == SCHED_FIFO)    ? "SCHED_FIFO"
                           : (policy == SCHED_RR)    ? "SCHED_RR"
                           : (policy == SCHED_OTHER) ? "SCHED_OTHER"
                                                     : "UNKNOWN";

  // Print information related to the thread running with such policy
  printf("Thread %d with sample %d is running with policy %s and priority %d\n",
         test->thread_num, test->sample, policy_str, param.sched_priority);

  struct timeval start, end;
  gettimeofday(&start, NULL);

  // Assign task to maximise CPU process
  CpuBoundTask();

  gettimeofday(&end, NULL);

  long elapsed_time =
      (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
  printf("Thread [%d] lasted: %ldus\n", test->thread_num, elapsed_time);
  printf("------------------------------\n");

  test->elapsed_time = elapsed_time;
}

void SpawnThread(ThreadSampleTest* test) {
  // Initiate thread attributes
  pthread_attr_t attr;
  struct sched_param param;
  pthread_attr_init(&attr);

  // Enable and set thread scheduling policy
  pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
  pthread_attr_setschedpolicy(&attr, test->policy);

  // Assign thread schedule priority
  param.sched_priority = test->priority;
  pthread_attr_setschedparam(&attr, &param);

  // Start thread
  pthread_create(&test->thread_id, &attr, ThreadFunction, test);
}

void JoinSamples(ThreadSampleTest* test) {
  // Join sample to cleanup
  pthread_join(test->thread_id, NULL);
}

FILE* HandleCsv() {
  // Create file in append mode
  FILE* csv = fopen("thread_times.csv", "a+");
  if (csv) {
    // Set csv title
    fprintf(csv,
            "ThreadNum, Sample, Policy, Priority, Elapsed_Time_Microseconds\n");
  } else {
    perror("Failed to open file");
    exit(1);
  }

  return csv;
}

void FillCsv(FILE* csv, ThreadSampleTest* test) {
  const char* policy_str = (test->policy == SCHED_FIFO)    ? "SCHED_FIFO"
                           : (test->policy == SCHED_RR)    ? "SCHED_RR"
                           : (test->policy == SCHED_OTHER) ? "SCHED_OTHER"
                                                           : "UNKNOWN";

  fprintf(csv, "%d, %d, %s, %d, %ld\n", test->thread_num, test->sample,
          policy_str, test->priority, test->elapsed_time);
}