#include "MousePlotter.h"

#include <curses.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRAIL_LENGTH 10

int x_char = 0;
int y_char = 0;
int prev_x_char = 0;
int prev_y_char = 0;
int row = 0, col = 0;
int ended_record = 0;
int time_sig = 0;
ull packed_position;
pthread_t updater;

static FILE* f_recorded_positions;

int trail_index = 0;
Position trail[TRAIL_LENGTH];

void InitPlotter(void) {
  // Open a binary file for reading and writing
  f_recorded_positions = fopen("positions.dat", "rb");
  if (f_recorded_positions == NULL) {
    perror("Failed to open file");
    exit(EXIT_FAILURE);
  }

  PrepareTimer();
}

void DisposePlotter(void) {
  // Close the file after writing
  fclose(f_recorded_positions);
}

void Unpack(ull packed, float* x, float* y) {
  int x_t = (int)(packed & 0xFFFFFFFF);
  int y_t = (int)((packed >> 32) & 0xFFFFFFFF);

  *x = *(float*)&x_t;
  *y = *(float*)&y_t;
}

void HandleTime(int sig) { time_sig = 1; }

void PrepareTimer(void) {
  // Prepare time handler function to react to signals
  struct sigaction action;
  action.sa_handler = HandleTime;
  action.sa_flags = 0;
  sigaction(SIGALRM, &action, NULL);

  // Create time instance with real time clock
  timer_t log_time_id;
  timer_create(CLOCK_REALTIME, NULL, &log_time_id);

  struct itimerspec timerParams;
  // Prepare clock step increment
  timerParams.it_value.tv_sec = 0;
  timerParams.it_value.tv_nsec = 10 * 1000000;

  // Prepare clock step interval increment
  timerParams.it_interval.tv_sec = 0;
  timerParams.it_interval.tv_nsec = 10 * 1000000;

  // Start time with parameters
  timer_settime(log_time_id, 0, &timerParams, NULL);
}

void* UpdatePosition(void*) {
  while (1) {
    if (time_sig != 1) {
      continue;
    }
    time_sig = 0;

    if (fread(&packed_position, sizeof(ull), 1, f_recorded_positions) == 1) {
      // Unpack the position into x and y
      float x, y;
      Unpack(packed_position, &x, &y);

      getmaxyx(stdscr, row, col);

      // Normalize coordinates
      x_char = (int)(x * col);
      y_char = row - (int)(y * row);

      trail[trail_index].x = x_char;
      trail[trail_index].y = y_char;

      trail_index = (trail_index + 1) % TRAIL_LENGTH;
    }

    if (feof(f_recorded_positions)) {
      break;
    }
  }
  ended_record = 1;
}

void Draw() {
  initscr();
  keypad(stdscr, TRUE);
  noecho();

  curs_set(0);
  pthread_create(&updater, NULL, UpdatePosition, NULL);

  while (!ended_record) {
    clear();
    mvprintw(0, 0,
             "(warning) Drawing can seem slow but it does display eventualy");

    // Print tray
    for (int i = 0; i < TRAIL_LENGTH; i++) {
      if (trail[i].x != 0 || trail[i].y != 0) {
        mvprintw(trail[i].y, trail[i].x, "*");
      }
    }

    // Print current position
    mvprintw(y_char, x_char, "*");
    refresh();
    usleep(100000);
  }

  endwin();
  pthread_join(updater, NULL);
}