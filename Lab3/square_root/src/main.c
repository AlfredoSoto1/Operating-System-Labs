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
  long buffer_length = 0;
  long n_read_values = 0;
  unsigned char* input_buffer = malloc(sizeof(unsigned char) * buffer_length);

  // Read data from file and store it on the buffer
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

double SqrtIter(double number, int n) {
  double guess = number / 2.0;

  for (int i = 0; i < n; i++) {
    guess = 0.5 * (guess + number / guess);
  }

  return guess;
  // if (n == 0) {
  //   return guess;
  // }

  // double better_guess = SqrtIter(number, guess / 2.0, n - 1) +
  //                       number / SqrtIter(number, guess / 2.0, n - 1);
  // return 0.5 * (better_guess);
}

void* FileHandlerOutput(void* param) {
  // Finally, the third thread gets the square root data and stores them in the
  // file sqrt.txt.
}

void BootFileHandler() {
  pthread_t file_handler_thread;

  int file_status;

  pthread_create(&file_handler_thread, NULL, FileHandlerPrepare, &file_status);
  pthread_join(file_handler_thread, NULL);

  if (file_status) {
    printf("File exists. Proceeding to do computation...\n");
  } else {
    printf("File buffer handled correctly...\n");
  }
}

int main() {
  //
  return 0;
}