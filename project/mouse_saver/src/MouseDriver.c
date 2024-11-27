#include "MouseDriver.h"

#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "MouseRecorder.h"

static int abs_x_pos;
static int abs_y_pos;
static MouseDriver driver;

void InitMouseDriver(void) {
  // Generic mouse device file
  driver.device = "/dev/input/mice";
  driver.x_pos = 0;
  driver.y_pos = 0;

  driver.max_x = 0;
  driver.max_y = 0;
  driver.least_x = 0;
  driver.least_y = 0;

  abs_x_pos = 0;
  abs_y_pos = 0;

  // Open the mice file content
  driver.f_device = open(driver.device, O_RDONLY);
  if (driver.f_device == -1) {
    perror("Error opening device");
    exit(EXIT_FAILURE);
  }

  // Prepare interruption signal to handle driver resources when program ends.
  struct sigaction action;
  action.sa_flags = 0;
  action.sa_handler = HandleMouseCleanup;
  sigaction(SIGINT, &action, NULL);

  InitMouseRecorder();
}

void DisposeMouseDriver(void) {
  // Close the file reference device to mouse data
  close(driver.f_device);
  DisposeMouseRecorder();
}

void HandleMouseCleanup(int signal) {
  char* debug = "Program Terminated successfully.\n";
  write(STDOUT_FILENO, debug, strlen(debug));

  DisposeMouseDriver();

  exit(EXIT_SUCCESS);
}

MouseDriver* GetMouseDriver(void) {
  // Return a reference of the singleton driver
  return &driver;
}

void GetMouse(Screen* screen) {
  // 3 bytes of data reserved for storing mouse delta position and mouse button
  // actions.
  signed char data[3];

  if (read(driver.f_device, data, sizeof(data)) > 0) {
    char left = data[0] & 0x1;    // mask for 1rst bit
    char right = data[0] & 0x2;   // mask for 2snd bit
    char middle = data[0] & 0x4;  // mask for 4rth bit

    // Mouse delta position
    abs_x_pos += data[1];
    abs_y_pos += data[2];

    if (abs_x_pos < driver.least_x) {
      driver.least_x = abs_x_pos;
    }

    if (abs_y_pos < driver.least_y) {
      driver.least_y = abs_y_pos;
    }

    if (abs_x_pos > driver.max_x) {
      driver.max_x = abs_x_pos;
    }

    if (abs_y_pos > driver.max_y) {
      driver.max_y = abs_y_pos;
    }

    driver.x_pos = abs_x_pos;
    driver.y_pos = abs_y_pos;

    printf("W:%d, H:%d, dx: %d, dy: %d x:%d, y:%d\n", screen->width,
           screen->height, driver.least_x, driver.max_x, driver.x_pos,
           driver.y_pos);

    RecordPoisitions(&driver);
  }
}