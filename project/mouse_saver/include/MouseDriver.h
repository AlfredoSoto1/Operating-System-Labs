#ifndef MOUSE_DRIVER_H
#define MOUSE_DRIVER_H

/**
 * @brief
 *
 */
typedef struct {
  int x_pos;
  int y_pos;
  char* device;
} MouseDriver;

/**
 * @brief
 *
 * @param driver
 * @return int
 */
int DriverInit(MouseDriver* driver);

void GetMouse() {}

#endif  // MOUSE_DRIVER_H