#include "imu_driver.h"

#include "MyTimer.h"

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
  double delta_time = timer_time - state->time;

  printf("Last time:%lf %lf %lf\n", state->time, delta_time, timer_time);

  // Set the current time
  state->time = timer_time;

  // Update bot's velocity
  state->v_x = state->v_x + state->acc_x * delta_time;
  state->v_y = state->v_y + state->acc_y * delta_time;

  // Update bot's position after calculating the new velocity
  state->p_x = state->p_x + state->v_x * delta_time;
  state->p_y = state->p_y + state->v_y * delta_time;
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
      }

      // Print data every 200ms
      // printf("%.2lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf\n", state.time,
      //        state.p_x, state.p_y, state.v_x, state.v_y, state.acc_x,
      //        state.acc_y);

      WriteCurrentState(imu_file, &state);

      // Increase the time by its assigned period
      timer_time += PERIOD_MS / 1000.0;
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

  char line[256];
  // Read each value from the imu_file line into the bot state.
  if (fgets(line, sizeof(line), imu_file) == NULL) {
    return -1;
  }

  // Parse the line using sscanf
  if (sscanf(line, "%lf, %lf, %lf, %lf, %lf, %lf, %lf", &state->time,
             &state->p_x, &state->p_y, &state->v_x, &state->v_y, &state->acc_x,
             &state->acc_y) != 7) {
    return -1;
  }
  return 0;
}

void WriteCurrentState(FILE* file, BotState* state) {
  // Move to the end of the file for appending
  fseek(file, 0, SEEK_END);

  // Write the new line to the file
  fprintf(file, "%.2lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf\n",
          state->time, state->p_x, state->p_y, state->v_x, state->v_y,
          state->acc_x, state->acc_y);
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

void LaunchImuDriver() {
  // Create timer
  PrepareTimer();

  // Open file or create if not existant
  FILE* imu_file = AccessImuData();

  // Update robot's state every 200ms
  PollSignalEvent(imu_file);

  fclose(imu_file);
}