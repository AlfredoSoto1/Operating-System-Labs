#include "task_measurer.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>

void GenerateSamples(ScheduleSampleTest* test) {
  // Memoize the averave time taken and each child's time for each sample
  test->avrg_time_taken = malloc(sizeof(double) * test->children);
  test->child_time_taken = malloc(sizeof(long*) * test->children);

  for (int i = 0; i < test->children; i++) {
    test->avrg_time_taken[i] = 0;
    test->child_time_taken[i] = malloc(sizeof(long) * test->samples);
  }

  for (int sample = 0; sample < test->samples; sample++) {
    HandleChildrenSample(test, sample);
  }

  for (int child = 0; child < test->children; child++) {
    printf("Avrg [%d] pri[%3d]: %lf\n", child, test->priorities[child],
           test->avrg_time_taken[child]);
  }
  printf("---------------------\n");
}

void FreeSamples(ScheduleSampleTest* test) {
  for (int i = 0; i < test->children; i++) {
    free(test->child_time_taken[i]);
  }
  free(test->child_time_taken);
  free(test->avrg_time_taken);
}

void HandleChildrenSample(ScheduleSampleTest* test, int sample) {
  // Hold all the process ids that will be forked
  pid_t* pids = malloc(sizeof(pid_t) * test->children);

  // Hold the start and end time for each process
  struct timeval start;
  struct timeval* end = malloc(sizeof(struct timeval*) * test->children);

  // Get initial time for partent process
  gettimeofday(&start, NULL);

  for (int i = 0; i < test->children; i++) {
    // Fork a new child process
    pids[i] = fork();

    if (pids[i] < 0) {
      perror("fork");
      exit(1);
    }

    if (pids[i] == 0) {
      // Set process priority for child
      if (setpriority(PRIO_PROCESS, getpid(), test->priorities[i]) < 0) {
        printf("[%d] Error setting priority\n", i);
        perror("setpriority");
        exit(1);
      }

      // Start the CPU-bound task
      CpuBoundTask();

      // Exit child
      exit(0);
    }
  }

  for (int i = 0; i < test->children; i++) {
    // Wait for child to finish
    waitpid(pids[i], NULL, 0);

    // Get the time after child's execution
    gettimeofday(&end[i], NULL);

    // Calculate the elapsed time and print it in microseconds
    long elapsed_time = (end[i].tv_sec - start.tv_sec) * 1000000 +
                        (end[i].tv_usec - start.tv_usec);
    printf("p[%d] pri[%3d] lifetime: %ldus\n", i, test->priorities[i],
           elapsed_time);

    // Save the time taken of the child after finishing the process
    test->child_time_taken[i][sample] = elapsed_time;
    test->avrg_time_taken[i] += elapsed_time / (double)test->samples;
  }

  free(end);
  free(pids);
}

void CpuBoundTask() {
  // Make CPU run at max
  for (volatile long i = 0; i < 1000000000; i++);
}