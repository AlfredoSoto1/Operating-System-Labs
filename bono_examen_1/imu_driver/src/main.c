#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>
#include <unistd.h>

#define PERIOD_MS 500

int enable_writing_flg = 0;

typedef struct {
  double time;
  double p_x;
  double p_y;
  double v_x;
  double v_y;
  double acc_x;
  double acc_y;
} BotState;

void InitBotState(BotState* state) {
  state->time = 0;
  state->p_x = 20;
  state->p_y = 10;
  state->v_x = 0;
  state->v_y = 0;
  state->acc_x = 0.15;  // m/s/s
  state->acc_y = 0.06;  // m/s/s
}

void UpdateBotState(BotState* state) {
  // Increase the time of the bot
  state->time += 0.2;

  // Update bot's velocity
  state->v_x = state->v_x + state->acc_x * state->time;
  state->v_y = state->v_y + state->acc_y * state->time;

  // Update bot's position after calculating the new velocity
  state->p_x = state->p_x + state->v_x * state->time;
  state->p_y = state->p_y + state->v_y * state->time;
}

void HandleTimeSignal(int sig) {
  // Enable writing after 200ms.
  enable_writing_flg = 1;

  // Print status for debug
  // char buf[64];
  // snprintf(buf, sizeof(buf), "Signal detected\n");
  // write(1, buf, strlen(buf));
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

void PollSignalEvent(FILE* imu_file) {
  while (1) {
    // Pause the process until a signal is received. This prevents CPU
    // saturation when running the while loop with no control.
    pause();

    // If the enable writing flag is set to enable, write to the file the
    // current bot's state and update it for when the next iteration take place.
    if (enable_writing_flg == 1) {
      enable_writing_flg = 0;

      BotState state;

      // Check if imu_data could be read (not empty)
      if (ReadPreviousState(imu_file, &state) == -1) {
        InitBotState(&state);
      } else {
        UpdateBotState(&state);
        printf("%.2lf, %lf, %lf, %lf, %lf, %lf, %lf\n", state.time, state.p_x,
               state.p_y, state.v_x, state.v_y, state.acc_x, state.acc_y);
      }

      WriteCurrentState(imu_file, &state);
    }
  }
}

int ReadPreviousState(FILE* imu_file, BotState* state) {
  // Set the starting reading position to the last byte in file.
  fseek(imu_file, 0, SEEK_END);

  // Get the position inside the file.
  long pos_in_file = ftell(imu_file);
  if (pos_in_file == 0) {
    return -1;  // The file is empty
  }

  int found_last_line = 0;
  while (pos_in_file > 0 && found_last_line != 2) {
    // Set the reading position to be the last position in file.
    fseek(imu_file, --pos_in_file, SEEK_SET);

    // Check if the last position that we are reading is a new line.
    found_last_line += (fgetc(imu_file) == '\n');
  }

  // If pos is 0, it means the file doesn't contain any newline
  if (pos_in_file == 0) {
    fseek(imu_file, 0, SEEK_SET);
  }

  // Read each value from the imu_file line into the bot state.
  if (fscanf(imu_file, "%.2lf, %lf, %lf, %lf, %lf, %lf, %lf", &state->time,
             &state->p_x, &state->p_y, &state->v_x, &state->v_y, &state->acc_x,
             &state->acc_y) != 7) {
    printf("error\n");
    return -1;  // Error reading values
  }

  return 0;
}

void WriteCurrentState(FILE* file, BotState* state) {
  // Move to the end of the file for appending
  fseek(file, 0, SEEK_END);

  // Write the new line to the file
  fprintf(file, "%.2lf, %lf, %lf, %lf, %lf, %lf, %lf\n", state->time,
          state->p_x, state->p_y, state->v_x, state->v_y, state->acc_x,
          state->acc_y);
  fflush(file);
}

FILE* AccessImuData() {
  // Open a file in read/write mode.
  FILE* imu_file = fopen("imu_data.txt", "r+");

  // If the file does not exist, open it in write/read mode.
  if (imu_file == NULL) {
    imu_file = fopen("imu_data.txt", "w+");
  }

  return imu_file;
}

int main() {
  PrepareTimer();

  FILE* imu_file = AccessImuData();

  PollSignalEvent(imu_file);

  fclose(imu_file);
  return 0;
}