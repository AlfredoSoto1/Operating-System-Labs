#ifndef MOUSE_PLOTTER_H
#define MOUSE_PLOTTER_H

#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

typedef unsigned long long ull;

typedef struct {
  int x;
  int y;
} MousePosition;

typedef struct {
  int x, y;
} Position;

/**
 * @brief Initiates the mouse plotter
 *
 */
void InitPlotter(void);

/**
 * @brief Frees any allocated data from the mouse plotter
 *
 */
void DisposePlotter(void);

/**
 * @brief Prepares timer signal
 *
 */
void PrepareTimer(void);

/**
 * @brief Unpacks the long variable into its x-y components
 *
 * @param packed
 * @param x
 * @param y
 */
void Unpack(ull packed, float* x, float* y);

/**
 * @brief Draws to the console the recorded coordinates
 *
 */
void Draw();

#endif  // MOUSE_PLOTTER_H