#include "MouseDriver.h"

#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>  // for setpriority
#include <sys/wait.h>
#include <unistd.h>

static MouseDriver driver;

void InitMouseDriver() {
  // Generic mouse device file
  driver.device = "/dev/input/mice";

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
}

void DisposeMouseDriver() {
  // Close the file reference device to mouse data
  close(driver.f_device);
}

void HandleMouseCleanup(int signal) {
  char* debug = "Program Terminated successfully.\n";
  write(STDOUT_FILENO, debug, strlen(debug));

  DisposeMouseDriver();

  exit(EXIT_SUCCESS);
}

void GetMouse() {
  // 3 bytes of data reserved for storing mouse delta position and mouse button
  // actions.
  signed char data[3];

  if (read(driver.f_device, data, sizeof(data)) > 0) {
    char left = data[0] & 0x1;    // mask for 1rst bit
    char right = data[0] & 0x2;   // mask for 2snd bit
    char middle = data[0] & 0x4;  // mask for 4rth bit

    // Mouse delta position
    int dx = data[1];
    int dy = data[2];

    printf("Left: %d, Right: %d, Middle: %d, dx: %d, dy: %d\n", left, right,
           middle, dx, dy);
  }
}