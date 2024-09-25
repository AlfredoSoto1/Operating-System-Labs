#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int exit_flag = 0;
float number = -1;
pthread_mutex_t mutex;
pthread_cond_t allow_listener;
pthread_cond_t allow_computation;

void* ListenerThread(void* param) {
  do {
    pthread_mutex_lock(&mutex);
    // Print prompt
    printf(
        "Enter a floating point number between [0, 1] to calculate it's "
        "arcsine:\n");
    // Read number from console
    scanf("%f", &number);
    // Wait for computation to be done
    pthread_cond_wait(&allow_computation, &mutex);

    pthread_mutex_unlock(&mutex);
  } while (1);
}

void* ArcsineThread(void* param) {
  do {
    pthread_mutex_lock(&mutex);
    if (number >= 0.0f && number <= 1.0f) {
      // Compute the arcsine of the entered float number
      float result = asin(number);
      printf("Computation of asin(%.4f) = %.4f\n", number, result);
    }
    // Let know the Listener that he can ask the user again
    pthread_cond_signal(&allow_computation);
    pthread_mutex_unlock(&mutex);
  } while (1);
}

int main() {
  pthread_t thread1, thread2;

  // Initialize mutex
  pthread_mutex_init(&mutex, NULL);

  // Create threads
  pthread_create(&thread1, NULL, ListenerThread, NULL);
  pthread_create(&thread2, NULL, ArcsineThread, NULL);

  // Wait for each thread to finish
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return 0;
}