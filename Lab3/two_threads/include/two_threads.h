#ifndef TWO_THREADS_H
#define TWO_THREADS_H

#include <pthread.h>

/**
 * @brief Thread locks holding the mutexes for blocking the threads
 */
typedef struct ThreadLocks {
  pthread_mutex_t mutex;
  pthread_cond_t allow_computation;
} ThreadLocks;

/**
 * @brief Current Program state. I handles if the program is ready to print or
 * exit respectively.
 */
typedef struct ProgramState {
  int exit_program;
  int ready_to_print;
} ProgramState;

/**
 * @brief Block of memory that holds the data that the following two threads
 * manage from user's input.
 */
typedef struct GlobalSpace {
  float number;
} GlobalSpace;

extern ThreadLocks locks;
extern ProgramState state_p;
extern GlobalSpace global_s;

/**
 * @brief Spawns the two threads that will execute two routines expressed as:
 * @note void *(*ProcessInput)(void *) - That will read the user's input.
 * @note void *(*ProcessComputation)(void *) - That will process the user's
 * input for asynchronous computation.
 */
void SpawnThreads();

/**
 * @brief This function listens for the user's input.
 *
 * @param param
 * @return void*
 */
void* ProcessInput(void* param);

/**
 * @brief This function computes in a asynchronously the input from the user.
 *
 * @param param
 * @return void*
 */
void* ProcessComputation(void* param);

#endif  // TWO_THREADS_H
