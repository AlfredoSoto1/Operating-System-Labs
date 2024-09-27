#include "FileHandler.h"
#include "RootTask.h"

int main() {
  // Boot file hander to generate the files if necesary
  BootFileHandler();

  // Runs the main three threads synchronously
  RunRootTask();
  return 0;
}