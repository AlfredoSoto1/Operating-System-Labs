#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>
#include <unistd.h>

#define PERIOD_MS 1500  // 1.5s

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
  // Prepare clock step increment
  timerParams.it_value.tv_sec = 0;
  timerParams.it_value.tv_nsec = PERIOD_MS * 1000000;

  // Prepare clock step interval increment
  timerParams.it_interval.tv_sec = 0;
  timerParams.it_interval.tv_nsec = PERIOD_MS * 1000000;

  // Start time with parameters
  timer_settime(log_time_id, 0, &timerParams, NULL);
}

int GetPidByName(const char *process_name) {
  char command[256];
  snprintf(command, sizeof(command), "pgrep -x %s", process_name);

  FILE *fp = popen(command, "r");
  if (fp == NULL) {
    perror("popen");
    return -1;
  }

  int pid = -1;
  if (fscanf(fp, "%d", &pid) == 1) {
    // Successfully retrieved a PID
  }

  pclose(fp);
  return pid;
}

void ProcessDriverSupervision() {
  while (1) {
    if (enable_imu_driver_detection == 1) {
      enable_imu_driver_detection = 0;

      int pid = GetPidByName("imu_driver");

      printf("imu_driver process: %d\n", pid);

      // If process is running, here is no need to fork it.
      if (pid != -1) {
        continue;
      }

      // pid_t imu_driver_process = fork();

      // if (imu_driver_process == 0) {
      //   execlp("imu_driver", "imu_driver", NULL);

      //   // Exit with parent with failure if exec() fails
      //   exit(EXIT_FAILURE);
      // }
    }

    // Sleep for 100ms
    usleep(100000);
  }
}

int main() {
  // Create timer
  PrepareTimer();

  ProcessDriverSupervision();
  return 0;
}