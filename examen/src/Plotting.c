#include "Plotting.h"

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>  // for setpriority
#include <sys/wait.h>
#include <unistd.h>

void PrintData(int sig) {
  for (int i = 0; i < 20; i++) {
    char data_to_print[15];
    snprintf(data_to_print, 10, "%d\n", plotting_block[i]);
    write(STDOUT_FILENO, data_to_print, strlen(data_to_print));
  }
}

void PrepareTimer() {
  // Set a signal event to customize the signal input
  struct sigevent clock_sig_event;
  clock_sig_event.sigev_notify = SIGEV_SIGNAL;
  clock_sig_event.sigev_signo = SIGUSR1;
  clock_sig_event.sigev_notify_attributes = NULL;

  // Prepare time handler function to react to signals
  struct sigaction action;
  action.sa_handler = PrintData;
  action.sa_flags = 0;
  sigaction(SIGUSR1, &action, NULL);

  // Create time instance with real time clock
  timer_t log_time_id;
  timer_create(CLOCK_REALTIME, &clock_sig_event, &log_time_id);

  struct itimerspec timerParams;
  // Prepare clock step increment
  timerParams.it_value.tv_sec = 1;
  timerParams.it_value.tv_nsec = 900 * 1000000;

  // Prepare clock step interval increment
  timerParams.it_interval.tv_sec = 2;
  timerParams.it_interval.tv_nsec = 200 * 1000000;

  // Start time with parameters
  timer_settime(log_time_id, 0, &timerParams, NULL);
}

void* ReadData(void*) {
  while (1) {
    // Read integer from terminal
    int input;
    scanf("%d", &input);

    // Set the data with the input value consecutively
    for (int i = 0; i < PAGE_SIZE; i++) {
      plotting_block[i] = input + i;
    }
  }
}

void RunTest() {
  printf("Process id %d\n", getpid());

  // Set priority to 0 (MAX)
  // System doesnt allow values under zero (needs to be sudo)
  // If you are sudo, you can use -20 as max priority
  if (setpriority(PRIO_PROCESS, getpid(), 0) < 0) {
    perror("setpriority");
    exit(1);
  }

  PrepareTimer();

  // Create page
  plotting_block = mmap(0xBEEDAD, PAGE_SIZE + 0xBEEDAD, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  // Create thread
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, ReadData, NULL);

  // Wait for thread to join
  pthread_join(thread_id, NULL);

  // Free page
  if (munmap(plotting_block, PAGE_SIZE) == -1) {
    perror("munmap failed");
    return 1;
  }
}