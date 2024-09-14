#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "Reader.h"
#include "Writer.h"

int main() {
  // Split into another process the reader logic
  // to measure the time it takes to read from a
  // shared memory block vs a memory queue block.
  int reader = fork();
  if (reader == 0) {
    printf("Started reader [%d]\n", getpid());
    RunSharedReader();

    RunReaderMQ();
    return 0;
  }

  // Split into another proces the writer logic
  // to measure the time it takes to write to a
  // shared memory block vs a memory queue block.
  int writer = fork();
  if (writer == 0) {
    printf("Started writer [%d]\n", getpid());
    RunSharedWriter();

    RunWriterMQ();
    return 0;
  }

  // Wait until both child processes end
  int reader_stat, writer_stat;
  waitpid(writer, &writer_stat, 0);
  waitpid(reader, &reader_stat, 0);

  printf("finished [reader: %d] [writer: %d]\n", reader, writer);

  return 0;
}