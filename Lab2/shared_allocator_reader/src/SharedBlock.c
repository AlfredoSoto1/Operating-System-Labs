#include "SharedBlock.h"

#include <stdlib.h>

SharedBlock CreateBlock(int blockSize) {
  SharedBlock block;

  block.token = ftok("/tmp", 65);

  // Validate token
  if (block.token == -1) {
    perror("ftok");
    block.error = 1;
  }

  // Locate the shared memory segment
  // shmid = shmget(key, SHM_SIZE, 0666);
  block.blockid = shmget(block.token, blockSize, 0666 | IPC_CREAT);
  if (block.blockid == -1) {
    perror("shmget failed");
    block.error = 2;
  }

  // map the block into the process adress space
  block.data = shmat(block.blockid, NULL, 0);

  // Handle if data could not be obtained
  if (block.data == (char *)-1) {
    perror("shmat failed");
    block.error = 3;
  }

  return block;
}

void DetachSharedBlock(SharedBlock *sharedBlock) {
  // Detach shared block
  shmdt(sharedBlock->data);
}

void FreeSharedBlock(SharedBlock *sharedBlock) {
  shmctl(sharedBlock->blockid, IPC_RMID, NULL);
}