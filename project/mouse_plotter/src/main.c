#include <stdio.h>

void printb(int number) {
  for (int i = 32 - 1; i >= 0; --i) {
    printf("%d", (number >> i) & 1);
  }
  printf("\n");
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