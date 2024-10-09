#ifndef IMU_DRIVER_H
#define IMU_DRIVER_H

#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  double time;
  double p_x;
  double p_y;
  double v_x;
  double v_y;
  double acc_x;
  double acc_y;
} BotState;

void InitBotState(BotState* state);

void UpdateBotState(BotState* state);
void PollSignalEvent(FILE* imu_file);

int ReadPreviousState(FILE* imu_file, BotState* state);

void WriteCurrentState(FILE* file, BotState* state);

FILE* AccessImuData();

void LaunchImuDriver();

#endif  // IMU_DRIVER_H