#ifndef SHARED_BLOCK_H
#define SHARED_BLOCK_H

#include <sys/ipc.h>
#include <sys/shm.h>

/**
 *
 */
typedef struct SharedBlock {
  void *data;
  int blockid;
  key_t token;
  int error;
} SharedBlock;

/**
 * @brief
 *
 * @param blockSize
 *
 * @return SharedBlock
 */
SharedBlock CreateBlock(int blockSize);

/**
 * @brief
 *
 * @param sharedBlock
 */
void DetachSharedBlock(SharedBlock *sharedBlock);

/**
 * @brief
 *
 * @param sharedBlock
 */
void FreeSharedBlock(SharedBlock *sharedBlock);

#endif  // SHARED_BLOCK_H