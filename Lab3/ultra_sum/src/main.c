#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "MyTime.h"

#define DATA_LENGTH 1000000  // One million

pthread_mutex_t mutex;

typedef struct SubSumatorBlock {
  int thread_num;
  int start;
  int end;
  int* data;
  long result;
} SubSumatorBlock;

void* SubSumator(void* params) {
  SubSumatorBlock* blocks = (SubSumatorBlock*)params;

  MyTime start = CurrentTimeMillis();
  for (int i = blocks->start; i < blocks->end; i++) {
    blocks->result += blocks->data[i];
  }
  MyTime end = CurrentTimeMillis();

  // Provide debug feedback
  printf("Thread %d, lasted: %lldms\n", blocks->thread_num, end - start);

  return NULL;
}

int main() {
  // Initialize array of one million integers
  int* numbers = malloc(DATA_LENGTH * sizeof(int));

  // Fill out the array from numbers of [1, 1000000]
  for (int i = 0; i < DATA_LENGTH; i++) {
    numbers[i] = i + 1;
  }

  SubSumatorBlock blocks[5];

  for (int i = 0; i < 5; i++) {
    blocks[i].thread_num = i + 1;
    blocks[i].data = numbers;
    blocks[i].result = 0;

    blocks[i].start = i * DATA_LENGTH / 5;
    blocks[i].end = (i + 1) * DATA_LENGTH / 5;
  }

  // Create and manage threads
  pthread_t sumator_thread[5];

  // Initialize mutex
  pthread_mutex_init(&mutex, NULL);

  // Create threads
  for (int i = 0; i < 5; i++) {
    pthread_create(&sumator_thread[i], NULL, SubSumator, &blocks[i]);
  }

  // Wait for each thread to finish
  for (int i = 0; i < 5; i++) {
    pthread_join(sumator_thread[i], NULL);
  }

  MyTime start = CurrentTimeMillis();

  long total_sum = 0;
  // Collect sum of each sub process computation
  for (int i = 0; i < 5; i++) {
    total_sum += blocks[i].result;
  }

  MyTime end = CurrentTimeMillis();

  printf("Total sum: %ld in %lldms\n", total_sum, end - start);

  free(numbers);

  return 0;
}