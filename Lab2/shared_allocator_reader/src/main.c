#include "Reader.h"
#include "Writer.h"

int main() {
  int reader = fork();
  if (reader == 0) {
    RunReader();
    return 0;
  }

  int writer = fork();
  if (writer == 0) {
    RunWriter();
    return 0;
  }

  int reader_stat, writer_stat;
  waitpid(writer, &writer_stat, 0);
  waitpid(reader, &reader_stat, 0);

  return 0;
}