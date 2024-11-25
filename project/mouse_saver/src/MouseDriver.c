#include "MouseDriver.h"

#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>

int DriverInit(MouseDriver* driver) {
  // Generic mouse device file
  driver->device = "/dev/input/mice";

  // Open the mice file content
  int fd = open(driver->device, O_RDONLY);
  if (fd == -1) {
    perror("Error opening device");
    return -1;
  }

  return fd;
}