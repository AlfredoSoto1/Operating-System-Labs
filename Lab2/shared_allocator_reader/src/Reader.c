#include "Reader.h"

#include <stdio.h>

#include "BlockSemaphore.h"
#include "SharedBlock.h"

void RunReader() {
  // Create a semaphore
  Semaphore sem = CreateSemaphore();

  if (sem.error != 0) return;

  // Create shared block memory
  SharedBlock block = CreateBlock(SHM_SIZE);

  if (block.error != 0) return;

  while (1) {
    // Syncronize the read data function with the semaphores
    SyncReceiver(&sem, ReadData, &block);
  }

  // Close the semaphore
  CloseSemaphore(&sem);

  // Detach the block
  DetachSharedBlock(&block);

  // After reading the data, delete all of it
  FreeSharedBlock(&block);
}

void ReadData(void* block) {
  SharedBlock* shd_block = (SharedBlock*)block;

  for (int i = 0; i < COUNT; i++) {
    int* val = (int*)shd_block->data;
    printf("Reader: Reading from shared memory: %d\n", val[i]);
  }
}