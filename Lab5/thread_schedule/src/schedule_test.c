#include "schedule_test.h"

#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

pthread_t t1, t2;

void* ThreadFunction(void* arg) {
  int num = *(int*)arg;

  int policy;
  struct sched_param param;
  pthread_getschedparam(pthread_self(), &policy, &param);

  const char* policy_str = (policy == SCHED_FIFO)    ? "SCHED_FIFO"
                           : (policy == SCHED_RR)    ? "SCHED_RR"
                           : (policy == SCHED_OTHER) ? "SCHED_OTHER"
                                                     : "UNKNOWN";

  printf("Thread %lu is running with policy %s and priority %d\n",
         pthread_self(), policy_str, param.sched_priority);

  int i = 0;
  while (i < 10) {
    // usleep(500000);
    for (volatile long j = 0; j < 1000000000; j++);
    printf("Thread %d running. iteration %d\n", num, i);
    i++;
  }
}

void SpawnThreadSamples() {
  int arg1 = 1, arg2 = 2;

  struct sched_param param;
  pthread_attr_t attr;

  pthread_attr_init(&attr);
  pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

  pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
  param.sched_priority = 50;
  pthread_attr_setschedparam(&attr, &param);
  pthread_create(&t1, &attr, ThreadFunction, &arg1);

  pthread_attr_init(&attr);
  pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

  pthread_attr_setschedpolicy(&attr, SCHED_RR);
  param.sched_priority = 50;
  pthread_attr_setschedparam(&attr, &param);
  pthread_create(&t2, &attr, ThreadFunction, &arg2);
}

void JoinSamples() {
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
}