#ifndef PROGRAM_THREADS_H
#define PROGRAM_THREADS_H

#include <pthread.h>

/**
 * @brief Holds the information related to the screen
 *
 */
typedef struct Screen {
  int row;
  int col;
  int render;
  int update;
  int counter;
} Screen;

/**
 * @brief Holds the thread information for each task
 *
 */
typedef struct Tasks {
  pthread_t render_thread;
  pthread_t update_thread;
  pthread_t counter_thread;
  pthread_t keyboard_input;

  pthread_mutex_t update_lock;
  pthread_mutex_t render_lock;
  pthread_mutex_t counter_lock;

  pthread_cond_t render_cond;
  pthread_cond_t update_cond;
  pthread_cond_t counter_cond;
} Tasks;

extern Tasks tasks;
extern unsigned int counter_val;

/**
 * @brief Processes the game render thread
 *
 * @param param
 * @return void*
 */
void* ProcessRender(void* param);

/**
 * @brief Processes the game update thread
 *
 * @param param
 * @return void*
 */
void* ProcessPosition(void* param);

/**
 * @brief Processes the game counter thread
 *
 * @param param
 * @return void*
 */
void* ProcessCounter(void* param);

/**
 * @brief Processes the game input via keyboard with a thread
 *
 * @param param
 * @return void*
 */
void* ProcessKeyboardInput(void* param);

/**
 * @brief Initializes the screen with default parameters and console
 *
 * @param screen
 */
void InitializeScreen(Screen* screen);

/**
 * @brief Prepares the Game thread tasks
 *
 */
void PrepareGame();

#endif  // PROGRAM_THREADS_H