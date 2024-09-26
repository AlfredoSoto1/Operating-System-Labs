#include "two_threads.h"

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

ThreadLocks locks;
ProgramState state_p;
GlobalSpace global_s;

void SpawnThreads() {
  // Set initial number value
  global_s.number = -1;

  // Set the initial program state
  state_p.exit_program = 0;
  state_p.ready_to_print = 0;

  pthread_t thread1, thread2;

  // Initialize mutex
  pthread_mutex_init(&locks.mutex, NULL);

  // Create threads
  pthread_create(&thread1, NULL, ProcessInput, NULL);
  pthread_create(&thread2, NULL, ProcessComputation, NULL);

  // Wait for each thread to finish
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  pthread_mutex_destroy(&locks.mutex);

  printf("Program ended\n");
}

void* ProcessInput(void* param) {
  do {
    pthread_mutex_lock(&locks.mutex);

    // Print and scan floating point number
    printf("Enter a floating point number between [0, 1]: \n");
    scanf("%f", &global_s.number);
    state_p.ready_to_print = 1;

    // Set exit contidion
    if (global_s.number > 100) {
      state_p.exit_program = 1;
      pthread_cond_signal(&locks.allow_computation);
      pthread_mutex_unlock(&locks.mutex);
      break;
    }

    // Notify the other thread
    pthread_cond_signal(&locks.allow_computation);

    // Make this thread wait for the computation thread locks the mutex
    pthread_cond_wait(&locks.allow_computation, &locks.mutex);
    pthread_mutex_unlock(&locks.mutex);
  } while (1);
}

void* ProcessComputation(void* param) {
  do {
    pthread_mutex_lock(&locks.mutex);

    // Wait until the other thread finished asking user
    if (!state_p.ready_to_print) {
      pthread_cond_wait(&locks.allow_computation, &locks.mutex);
    }

    if (state_p.exit_program) {
      pthread_mutex_unlock(&locks.mutex);
      break;
    }

    // Perform computation if lays under domain
    if (global_s.number >= 0.0f && global_s.number <= 1.0f) {
      float result = asin(global_s.number);
      printf("Computation of asin(%.4f) = %.4f\n", global_s.number, result);
    } else {
      printf("Number %.6f is out of range [0, 1].\n", global_s.number);
    }

    // Flag that is not ready to print
    state_p.ready_to_print = 0;

    pthread_cond_signal(&locks.allow_computation);
    pthread_mutex_unlock(&locks.mutex);
  } while (1);
}