#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int exit_flag = 0;
float number = -1;
pthread_mutex_t mutex;

void* ListenerThread(void* param) {
  do {
    pthread_mutex_lock(&mutex);
    printf(
        "Enter a floating point number between [0, 1] to calculate it's "
        "arcsine:\n");

    scanf("%f", &number);

    if (number > 1.0f) {
      exit_flag = 1;
    }
    pthread_mutex_unlock(&mutex);

  } while (!exit_flag);
}

void* ArcsineThread(void* param) {
  do {
    if (number >= 0.0f && number <= 1.0f) {
      pthread_mutex_lock(&mutex);
      float result = asin(number);
      printf("Arcsine of %.4f is %.4f\n", number, result);

      // Make the number negative to stop this thread from spamming into the
      // console the value
      number = -1;
      pthread_mutex_unlock(&mutex);
    }

  } while (!exit_flag);
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