#include "FileHandler.h"

#include <pthread.h>
#include <stdlib.h>

void WriteToFile(FILE* file) {
  // Set the seed
  srand(time(0));

  // Iterate over all lines of the file to be set a new value
  for (int i = 0; i < LENGTH_OF_FILE; i++) {
    unsigned char number = rand() % 256;
    fprintf(file, "%d\n", (unsigned char)(number * number));
  }
}

void* FileHandlerPrepare(void* param) {
  int exit_flag = *(int*)param;

  // Try to open the file containing the numbers.
  FILE* file = fopen("numbers.txt", "r");

  if (file != NULL) {
    printf("Numbers file exists.\n");
    fclose(file);
    // Exit with flag of 1 if the number's file already exists
    exit_flag = 1;
    return NULL;
  }

  printf("File does not exist. Creating and writing numbers.\n");

  // Create the file in write mode
  file = fopen("numbers.txt", "w");

  if (file == NULL) {
    printf("Error creating file.\n");
    exit_flag = -1;
    return NULL;
  }

  WriteToFile(file);

  fclose(file);
  printf("Numbers written to file.\n");
  exit_flag = 0;

  return NULL;
}

void BootFileHandler() {
  pthread_t file_handler_thread;

  int file_status;

  pthread_create(&file_handler_thread, NULL, FileHandlerPrepare, &file_status);
  pthread_join(file_handler_thread, NULL);

  if (file_status == -1) {
    exit(1);  // Could not handle file correctly
  }

  if (!file_status) {
    printf("File buffer handled correctly...\n");
  }
}