#include "RootTask.h"

#include <pthread.h>
#include <stdlib.h>

#include "FileHandler.h"
#include "MyTime.h"
#include "SqrtFunction.h"

RootTask root_task;

pthread_mutex_t read_compute_mutex;
pthread_mutex_t write_compute_mutex;
pthread_cond_t allow_computation;
pthread_cond_t output_results;

void* BufferHandler(void* param) {
  FILE* file = fopen("numbers.txt", "r");

  MyTime start = CurrentTimeMillis();

  // Read all lines and store them into the input_buffer
  char line[50];
  while (fgets(line, sizeof(line), file)) {
    pthread_mutex_lock(&read_compute_mutex);
    root_task.input_buffer[root_task.n_read_values++] =
        (unsigned char)atoi(line);

    pthread_cond_signal(&allow_computation);
    pthread_mutex_unlock(&read_compute_mutex);
  }

  MyTime end = CurrentTimeMillis();

  printf("Time Buffer Handler: %lldms\n", end - start);

  fclose(file);
  return NULL;
}

void* ComputeSqrt(void* param) {
  MyTime start = CurrentTimeMillis();

  for (unsigned long i = 0; i < LENGTH_OF_FILE; i++) {
    pthread_mutex_lock(&read_compute_mutex);

    if (i >= root_task.n_read_values) {
      pthread_cond_wait(&allow_computation, &read_compute_mutex);
    }

    root_task.processed_buffer[i] = SqrtFunction(root_task.input_buffer[i]);
    root_task.n_processed_values++;

    pthread_cond_signal(&output_results);

    pthread_mutex_unlock(&read_compute_mutex);
  }

  MyTime end = CurrentTimeMillis();
  printf("Time Compute Sqrt: %lldms\n", end - start);
  return NULL;
}

void* FileHandlerOutput(void* param) {
  FILE* file = fopen("sqrt.txt", "r");

  if (file == NULL) {
    file = fopen("sqrt.txt", "w");
  }

  MyTime start = CurrentTimeMillis();
  for (int i = 0; i < LENGTH_OF_FILE; i++) {
    pthread_mutex_lock(&write_compute_mutex);

    if (i == root_task.n_processed_values) {
      pthread_cond_wait(&output_results, &write_compute_mutex);
    }

    fprintf(file, "%f\n", root_task.processed_buffer[i]);
    pthread_mutex_unlock(&write_compute_mutex);
  }
  MyTime end = CurrentTimeMillis();
  printf("Time File Output: %lldms\n", end - start);

  fclose(file);
  return NULL;
}

void RunRootTask() {
  // Initialize root task fields
  root_task.input_buffer = NULL;
  root_task.n_read_values = 0;
  root_task.input_buffer = malloc(sizeof(unsigned char) * LENGTH_OF_FILE);
  root_task.processed_buffer = malloc(sizeof(double) * LENGTH_OF_FILE);

  // Initialize task threads
  pthread_t file_output_thread;
  pthread_t compute_sqrt_thread;
  pthread_t buffer_handler_thread;

  pthread_mutex_init(&read_compute_mutex, NULL);
  pthread_mutex_init(&write_compute_mutex, NULL);

  pthread_create(&compute_sqrt_thread, NULL, ComputeSqrt, NULL);
  pthread_create(&file_output_thread, NULL, FileHandlerOutput, NULL);
  pthread_create(&buffer_handler_thread, NULL, BufferHandler, NULL);

  // Wait for threads to finish
  pthread_join(compute_sqrt_thread, NULL);
  pthread_join(file_output_thread, NULL);
  pthread_join(buffer_handler_thread, NULL);

  pthread_mutex_destroy(&read_compute_mutex);
  pthread_mutex_destroy(&write_compute_mutex);

  free(root_task.input_buffer);
  free(root_task.processed_buffer);
}