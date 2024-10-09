
#include "MyTimer.h"

#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>
#include <unistd.h>

double timer_time = 0.0;
int enable_writing_flg = 0;

void HandleTimeSignal(int sig) {
  // Enable writing after 200ms.
  enable_writing_flg = 1;
}

void PrepareTimer() {
  // Create time instance with real time clock
  timer_t log_time_id;
  timer_create(CLOCK_REALTIME, NULL, &log_time_id);

  // Prepare time handler function to react to signals
  struct sigaction action;
  action.sa_handler = HandleTimeSignal;
  action.sa_flags = 0;
  sigaction(SIGALRM, &action, NULL);

  struct itimerspec timerParams;
  // Prepare clock step increment
  timerParams.it_value.tv_sec = 0;
  timerParams.it_value.tv_nsec = PERIOD_MS * 1000000;

  // Prepare clock step interval increment
  timerParams.it_interval.tv_sec = timerParams.it_value.tv_sec;
  timerParams.it_interval.tv_nsec = timerParams.it_value.tv_nsec;

  // Start time with parameters
  timer_settime(log_time_id, 0, &timerParams, NULL);
}