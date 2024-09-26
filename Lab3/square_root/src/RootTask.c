#include "RootTask.h"

#include <pthread.h>

#include "FileHandler.h"
#include "SqrtFunction.h"

RootTask root_task;

void* BufferHandler(void* param) {
  // The first thread is responsible for reading the data from the file
  // individually and storing them in an array named input_buffer using an index
  // named n_read_values to indicate how many values have been read from the
  // file.

  FILE* file = fopen("numbers.txt", "r");

  while (fgets(root_task.input_buffer, sizeof(buffer), file)) {
    printf("%s", buffer);
  }

  malloc(sizeof(unsigned char) * buffer_length);

  // Read data from file and store it on the buffer
  ReadFromFile(&, &root_task.n_read_values);
}

void* ComputeSqrt(void* param) {
  // The second thread is responsible for processing the data. Its job is to
  // iteratively calculate the square root of input_buffer using the following
  // formula:
  // y_n = 1/2(y_n-1 + R/(y_n-1))
  //
  // Where yn  is the current value, yn-1 is the previous value, and R  is the
  // number you want to calculate the square root from. The algorithm is
  // considered to converge after the 10th iteration. Use R/2  as the initial
  // value for yn-1.

  // This thread must use the value of n_read_values to avoid accessing
  // positions that have not been written yet. On the other hand, the processed
  // values must be written in another buffer named processed_buffer and another
  // index named n_processed_values.
}

void* FileHandlerOutput(void* param) {
  // Finally, the third thread gets the square root data and stores them in the
  // file sqrt.txt.
}

void RunRootTask() {
  // Initialize root task fields
  root_task.input_buffer = NULL;
  root_task.n_read_values = 0;

  // Initialize task threads
  pthread_t file_output_thread;
  pthread_t compute_sqrt_thread;
  pthread_t buffer_handler_thread;

  pthread_create(&compute_sqrt_thread, NULL, ComputeSqrt, NULL);
  pthread_create(&file_output_thread, NULL, FileHandlerOutput, NULL);
  pthread_create(&buffer_handler_thread, NULL, BufferHandler, NULL);

  // Wait for threads to finish
  pthread_join(compute_sqrt_thread, NULL);
  pthread_join(file_output_thread, NULL);
  pthread_join(buffer_handler_thread, NULL);
}