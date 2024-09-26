#include <pthread.h>

void* FileHandlerPrepare(void* param) {
  // Write a program that, as soon as it starts, creates an initial thread that
  // checks if the file data.txt exists.If it already exists, the thread
  // returns 1. If it does not exist, the thread creates the file and writes 10,
  // 000 pseudo - random unsigned 8 - bit integer values, one below the other,
  // and returns 0.
}

void* BufferHandler(void* param) {
  // The first thread is responsible for reading the data from the file
  // individually and storing them in an array named input_buffer using an index
  // named n_read_values to indicate how many values have been read from the
  // file.
}

void* CalculateSqrt(void* param) {
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

int main() {
  pthread_t file_handler_thread;

  int file_status;

  pthread_create(&file_handler_thread, NULL, FileHandlerPrepare, &file_status);

  pthread_join(file_handler_thread, NULL);

  return 0;
}