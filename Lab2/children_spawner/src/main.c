#include "spawner.h"

#define PROCESS_COUNT 3

int main() {
  int child_ids[PROCESS_COUNT];

  // Spawn 3 children
  for (int i = 0; i < PROCESS_COUNT; i++) {
    // Set the program to be a process of
    child_ids[i] = SpawnChildren("../greetings/Greetings");
  }

  WaitForChildren(child_ids, PROCESS_COUNT);
  return 0;
}