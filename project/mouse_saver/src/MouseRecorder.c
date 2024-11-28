#include "MouseRecorder.h"

#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static FILE* f_recorded_positions;

void InitMouseRecorder(void) {
  // Create file with permissions if it doesnt exist
  mode_t old_umask = umask(0);
  int fd = open("positions.dat", O_CREAT | O_RDWR, 0666);
  if (fd == -1) {
    perror("Failed to create or open positions.dat");
    exit(EXIT_FAILURE);
  }
  close(fd);
  umask(old_umask);

  // Open a binary file for reading and writing
  f_recorded_positions = fopen("positions.dat", "w+b");
  if (f_recorded_positions == NULL) {
    perror("Failed to open file");
    exit(EXIT_FAILURE);
  }
}

void DisposeMouseRecorder(void) {
  // Close the file after writing
  fclose(f_recorded_positions);

  AdjustPositionsBeforeExit();
}

void AdjustPositionsBeforeExit(void) {
  FILE* f_temp = fopen("positions.dat", "r+b");
  if (f_temp == NULL) {
    perror("Failed to open positions file for reading");
    return;
  }

  MouseDriver* driver = GetMouseDriver();
  ull packed_position;
  int x, y;

  // Read each packed position from the file
  while (fread(&packed_position, sizeof(ull), 1, f_temp) == 1) {
    // Unpack the position into x and y
    Unpack(packed_position, &x, &y);

    // Adjust the position based on the least_x and least_y
    if (driver->least_x < 0) {
      x += -driver->least_x;
    }

    if (driver->least_y < 0) {
      y += -driver->least_y;
    }

    float w = abs(driver->least_x - driver->max_x);
    float h = abs(driver->least_y - driver->max_y);
    // Re-pack the modified position
    packed_position = PackF(x / w, y / h);

    // Move the file pointer back to the previous position to overwrite
    fseek(f_temp, -sizeof(ull), SEEK_CUR);
    fwrite(&packed_position, sizeof(ull), 1, f_temp);
  }

  fclose(f_temp);
}

void RecordPoisitions(MouseDriver* driver) {
  // Pack two positions into one long variable
  ull packed_position = Pack(driver->x_pos, driver->y_pos);

  // Write bits into dat file
  fwrite(&packed_position, sizeof(ull), 1, f_recorded_positions);
}

ull Pack(int x, int y) {
  ull packed = 0;

  packed |= ((ull)x & 0xFFFFFFFF);
  packed |= ((ull)y & 0xFFFFFFFF) << 32;

  return packed;
}

ull PackF(float x, float y) {
  int x_t = *(int*)&x;
  int y_t = *(int*)&y;
  ull packed = 0;

  packed |= ((ull)x_t & 0xFFFFFFFF);
  packed |= ((ull)y_t & 0xFFFFFFFF) << 32;

  return packed;
}

void Unpack(ull packed, int* x, int* y) {
  *x = (int)(packed & 0xFFFFFFFF);
  *y = (int)((packed >> 32) & 0xFFFFFFFF);
}
