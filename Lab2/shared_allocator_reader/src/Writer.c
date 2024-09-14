#include "Writer.h"

#include <stdio.h>

#include "BlockSemaphore.h"
#include "SharedBlock.h"

void RunWriter() {
  // Create a semaphore
  Semaphore sem = CreateSemaphore();

  if (sem.error != 0) return;

  // Create shared block memory
  SharedBlock block = CreateBlock(SHM_SIZE);

  if (block.error != 0) return;

  printf("writing will start\n");
  // Write to the shared memory the data
  for (int i = 0; i < COUNT; i++) {
    SyncSender(&sem, WriteData, &block);
  }

  // Close the semaphore
  CloseSemaphore(&sem);

  // Detach the block
  DetachSharedBlock(&block);
}

void WriteData(void* block) {
  static long counter = 0;

  SharedBlock* shd_block = (SharedBlock*)block;

  // Turn the void* to int*
  long* reserved_data = (long*)shd_block->data;

  // Write the numbers to the data array buffer
  reserved_data[counter] = counter;

  counter++;
}