#include "Writer.h"

#include <stdio.h>

#include "BlockSemaphore.h"
#include "MemoryQueue.h"
#include "MyTime.h"
#include "SharedBlock.h"

void RunSharedWriter() {
  // Create a semaphore
  Semaphore sem = CreateSemaphore();

  if (sem.error != 0) return;

  // Create shared block memory
  SharedBlock block = CreateBlock(SHM_SIZE);

  if (block.error != 0) return;

  // Sync some process to produce
  SyncSender(&sem, WriteSharedData, &block);

  // Close the semaphore
  CloseSemaphore(&sem);

  // Detach the block
  DetachSharedBlock(&block);
}

void WriteSharedData(SharedBlock* block) {
  MyTime intiial_time = CurrentTimeMillis();

  for (int i = 0; i < COUNT; i++) {
    // Turn the void* to int*
    int* val = (int*)block->data;

    // Write the numbers to the data array buffer
    val[i] = i + 1;
  }

  MyTime elapsed_time = CurrentTimeMillis() - intiial_time;

  printf("Time Taken to write [SHM]: %lldms\n", elapsed_time);
}

void RunWriterMQ() {
  // Create queue
  Queue queue = CreateMemoryQueue();

  if (queue.error != 0) return;

  MyTime intiial_time = CurrentTimeMillis();
  for (int i = 1; i <= COUNT; ++i) {
    int* data = (int*)queue.buffer;
    *data = i;
    Enqueue(&queue);
  }

  MyTime elapsed_time = CurrentTimeMillis() - intiial_time;

  printf("Time Taken to write [QUEUE]: %lldms\n", elapsed_time);

  CloseQueue(&queue);

  // The reader will be incharged of freeing the queue
}