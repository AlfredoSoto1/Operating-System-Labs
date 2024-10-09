#include "MyTimer.h"

#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>
#include <unistd.h>

int enable_imu_driver_detection = 0;

void HandleTimeSignal(int sig) {
  // Enable the driver detection flag
  enable_imu_driver_detection = 1;
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
  timerParams.it_value.tv_sec = PERIOD_MS / 1000;
  timerParams.it_value.tv_nsec = (PERIOD_MS % 1000) * 1000000L;
  timerParams.it_interval.tv_sec = timerParams.it_value.tv_sec;
  timerParams.it_interval.tv_nsec = timerParams.it_value.tv_nsec;

  // Start time with parameters
  timer_settime(log_time_id, 0, &timerParams, NULL);
}
