#ifndef PROGRAM_THREADS_H
#define PROGRAM_THREADS_H

#define ENTER_NCURSES 10

typedef struct BallProperties {
  int x;
  int y;
  int dx;
  int dy;
} BallProperties;

typedef struct Screen {
  int row;
  int col;
} Screen;

typedef struct ProcessPositionParams {
  Screen* screen;
  BallProperties* properties;
} ProcessPositionParams;

/**
 * @brief Processes the update of the position of the particle
 *
 * @param param
 * @return void*
 */
void* ProcessPosition(void* param);

/**
 * @brief Processes the game counter
 *
 * @param param
 * @return void*
 */
void* ProcessCounter(void* param);

/**
 * @brief Waits for user to kick off the application
 *
 */
void WaitForUser();

/**
 * @brief Prepares the render loop and update threads
 *
 */
void PrepareRender();

#endif  // PROGRAM_THREADS_H