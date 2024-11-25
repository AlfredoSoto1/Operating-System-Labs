#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>

void printb(int number) {
  for (int i = 32 - 1; i >= 0; --i) {
    printf("%d", (number >> i) & 1);
  }
  printf("\n");
}

void capture() {
  const char* device = "/dev/input/mice";  // Generic mouse device file
  int fd = open(device, O_RDONLY);
  if (fd == -1) {
    perror("Error opening device");
    return -1;
  }

  signed char data[3];

  printf("Listening for mouse events. Move the mouse or press buttons.\n");
  while (1) {
    if (read(fd, data, sizeof(data)) > 0) {
      int left = data[0] & 0x1;
      int right = data[0] & 0x2;
      int middle = data[0] & 0x4;
      int dx = data[1];
      int dy = data[2];

      printf("Left: %d, Right: %d, Middle: %d, dx: %d, dy: %d\n", left, right,
             middle, dx, dy);
    }
  }

  close(fd);
}

int main() {
  unsigned char x1 = 2;
  unsigned char y1 = 5;

  unsigned char x2 = 7;
  unsigned char y2 = 9;

  int packed_x = (x1 << 8 | x2);
  int packed_y = (y1 << 8 | y2);

  long packed = (packed_x << 16 | packed_y);

  // printb(packed_x);
  // printb(packed_y);
  // printb(packed_x + packed_y);

  int result = packed_x + packed_y;
  printf("%d\n", result & 0xFF);
  printf("%d\n", (result >> 8) & 0xFF);
  printf("%d\n", (result >> 16) & 0xFF);
  printf("%d\n", (result >> 24) & 0xFF);
  return 0;
}