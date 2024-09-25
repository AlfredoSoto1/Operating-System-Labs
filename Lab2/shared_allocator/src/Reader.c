#include "Reader.h"

#include <stdio.h>

#include "BlockSemaphore.h"
#include "MemoryQueue.h"
#include "MyTime.h"
#include "SharedBlock.h"

void RunSharedReader() {
  // Create a semaphore
  Semaphore sem = CreateSemaphore();

  if (sem.error != 0) return;

  // Create shared block memory
  SharedBlock block = CreateBlock(SHM_SIZE);

  if (block.error != 0) return;

  SyncReceiver(&sem, ReaderSharedData, &block);

  // Close the semaphore
  CloseSemaphore(&sem);
  FreeSemaphore(&sem);

  // Detach the block
  DetachSharedBlock(&block);
  FreeSharedBlock(&block);
}

void ReaderSharedData(SharedBlock* block) {
  MyTime intiial_time = CurrentTimeMillis();

  long sum = 0;
  for (int i = 0; i < COUNT; i++) {
    int* val = (int*)block->data;
    sum += val[i];
  }
  printf("The sum of the numbers [SHM] is: %ld\n", sum);

  MyTime elapsed_time = CurrentTimeMillis() - intiial_time;

  printf("Time Taken to read [SHM]: %lldms\n", elapsed_time);
}

void RunReaderMQ() {
  // Create queue
  Queue queue = CreateMemoryQueue();

  if (queue.error != 0) return;

  MyTime intiial_time = CurrentTimeMillis();
  long sum = 0;

  for (int i = 0; i < COUNT; i++) {
    // Read from queue the front block data
    queue.bytes_read = Dequeue(&queue);

    // If it coudn't read any bytes, exit
    if (queue.bytes_read == -1) {
      perror("mq_receive");
      break;
    }

    sum += *(int*)queue.buffer;
  }

  printf("The sum of the numbers [QUEUE] is: %ld\n", sum);

  MyTime elapsed_time = CurrentTimeMillis() - intiial_time;

  printf("Time Taken to read [QUEUE]: %lldms\n", elapsed_time);

  CloseQueue(&queue);
  FreeQueue(&queue);
}