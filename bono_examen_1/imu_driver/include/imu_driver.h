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

/**
 * @brief Initializes the bot state with the default set values.
 *
 * @param state
 */
void InitBotState(BotState* state);

/**
 * @brief Updates the bot state with the movement formulas.
 *
 * @param state
 */
void UpdateBotState(BotState* state);

/**
 * @brief Polls the signal received every 200ms from the timer signal.
 *
 * @param imu_file
 */
void PollSignalEvent(FILE* imu_file);

/**
 * @brief Reads the last state written into the imu_data
 *
 * @param imu_file
 * @param state
 * @return a positive number if has read successfully
 */
int ReadPreviousState(FILE* imu_file, BotState* state);

/**
 * @brief Writes the current bot state into the imu_data,
 *
 * @param file
 * @param state
 */
void WriteCurrentState(FILE* file, BotState* state);

/**
 * @brief Accesses the imu file if it exists. If it doesnt, it will create it.
 *
 * @return imu_data file
 */
FILE* AccessImuData();

/**
 * @brief Launches the imu_driver app
 *
 */
void LaunchImuDriver();

#endif  // IMU_DRIVER_H