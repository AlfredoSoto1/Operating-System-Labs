#include <pthread.h>
#include <stdlib.h>

unsigned char* input_buffer;

void* FileHandlerPrepare(void* param) {
  // Write a program that, as soon as it starts, creates an initial thread that
  // checks if the file data.txt exists.If it already exists, the thread
  // returns 1. If it does not exist, the thread creates the file and writes 10,
  // 000 pseudo - random unsigned 8 - bit integer values, one below the other,
  // and returns 0.

  int file;
  int numbers[5];

  // Try to open the file for reading
  file = fopen("numbers.txt", "r");

  if (file != NULL) {
    // If the file exists, read and print its contents
    printf("File exists. Reading content:\n");
    for (int i = 0; i < 5; i++) {
      fscanf(file, "%d", &numbers[i]);  // Read each integer
      printf("Number %d: %d\n", i + 1, numbers[i]);
    }
    fclose(file);  // Close the file after reading
  } else {
    // If the file doesn't exist, create and write 5 numbers
    printf("File does not exist. Creating and writing numbers.\n");
    file = fopen("numbers.txt", "w");

    if (file == NULL) {
      printf("Error creating file.\n");
      return 1;
    }

    // Write 5 numbers into the file
    for (int i = 1; i <= 5; i++) {
      fprintf(file, "%d\n", i * 10);  // Writing numbers (10, 20, 30, 40, 50)
    }

    fclose(file);  // Close the file after writing
    printf("Numbers written to file.\n");
  }
}

void* BufferHandler(void* param) {
  // The first thread is responsible for reading the data from the file
  // individually and storing them in an array named input_buffer using an index
  // named n_read_values to indicate how many values have been read from the
  // file.
  long buffer_length = 0;
  long n_read_values = 0;
  input_buffer = malloc(sizeof(unsigned char) * buffer_length);

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

double SqrtFunction(double number) {
  double guess = number / 2.0;
  // Iterate over the function iteratively over 10 terms.
  for (int i = 0; i < 10; i++) {
    guess = 0.5 * (guess + number / guess);
  }
  return guess;
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
  printf("sqrt %lf\n", SqrtFunction(2));
  return 0;
}