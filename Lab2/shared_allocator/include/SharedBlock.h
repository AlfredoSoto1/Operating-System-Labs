#ifndef SHARED_BLOCK_H
#define SHARED_BLOCK_H

#include <sys/ipc.h>
#include <sys/shm.h>

/**
 * @brief SharedBlock structure
 */
typedef struct SharedBlock {
  void *data;
  int blockid;
  key_t token;
  int error;
} SharedBlock;

/**
 * @brief Creates in memory a block of shared memory to use across processes
 *
 * @param blockSize
 *
 * @return SharedBlock
 */
SharedBlock CreateBlock(int blockSize);

/**
 * @brief It "closes" the connection between the program and the shared block
 * provided.
 *
 * @param sharedBlock
 */
void DetachSharedBlock(SharedBlock *sharedBlock);

/**
 * @brief Frees the given shared memory block located at /dev/shm/
 *
 * @param sharedBlock
 */
void FreeSharedBlock(SharedBlock *sharedBlock);

#endif  // SHARED_BLOCK_H