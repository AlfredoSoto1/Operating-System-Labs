#include "Supervisor.h"

#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>
#include <unistd.h>

#include "MyTimer.h"

static pid_t imu_driver_process;

int GetPidByName(const char* process_name) {
  char command[256];
  snprintf(command, sizeof(command), "pgrep -x %s", process_name);

  FILE* fp = popen(command, "r");
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

void RelaunchImuDriver() {
  imu_driver_process = fork();

  if (imu_driver_process < 0) {
    perror("fork");
    return;
  }

  if (imu_driver_process == 0) {
    execlp("./imu_driver", "imu_driver", NULL);

    perror("execlp");
    exit(EXIT_FAILURE);
  } else {
    printf("Relaunched imu_driver: [pid: %d]\n", imu_driver_process);
    DetachProcessWaiting();
  }
}

void ProcessDriverSupervision() {
  while (1) {
    // Sleep for 100ms
    usleep(100000);

    if (enable_imu_driver_detection == 1) {
      enable_imu_driver_detection = 0;

      // Output pid for debug
      int pid = GetPidByName("imu_driver");
      printf("imu_driver process: %d\n", pid);

      if (pid < 0) {
        RelaunchImuDriver();
      }
    }
  }
}

void DetachProcessWaiting() {
  pthread_t imu_waiting_thread;
  pthread_create(&imu_waiting_thread, NULL, WaitForImuTermination, NULL);
  pthread_detach(imu_waiting_thread);
}

void* WaitForImuTermination(void* param) {
  int status;
  // Wait for the imu_driver process to terminate
  waitpid(imu_driver_process, &status, 0);

  // Exit thread once finished waiting
  pthread_exit(NULL);
}
