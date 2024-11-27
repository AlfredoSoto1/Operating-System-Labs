#include "Screen.h"

#include <errno.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

Screen screen;

void InitScreenBuffer(void) {
  // Open file on screen resolution
  int fb = open("/dev/fb0", O_RDONLY);
  if (fb == -1) {
    perror("Error opening framebuffer device");
    exit(EXIT_FAILURE);
  }

  struct fb_var_screeninfo vinfo;
  if (ioctl(fb, FBIOGET_VSCREENINFO, &vinfo)) {
    perror("Error reading screen information");
    close(fb);
    exit(EXIT_FAILURE);
  }

  printf("Screen Resolution: %dx%d\n", vinfo.xres, vinfo.yres);

  screen.width = vinfo.xres;
  screen.height = vinfo.yres;

  close(fb);
}

void DisposeScreenBuffer(void) {}

Screen* GetScreen(void) {
  // Return the screen singleton
  return &screen;
}