#ifndef BLOCK_SEMAPHORE_H
#define BLOCK_SEMAPHORE_H

#include <semaphore.h>

#define SEM_PRODUCER "/producer"
#define SEM_CONSUMER "/consumer"

typedef struct SharedBlock SharedBlock;

/**
 * @brief SyncFunc abstraction for function pointers when calling the async
 * function
 */
typedef void (*SyncFunc)(void *);

/**
 * @brief Semaphore structure with the knowledge of the producer and consumer
 *
 */
typedef struct Semaphore {
  sem_t *producer;
  sem_t *consumer;
  int error;
} Semaphore;

/**
 * @brief Creates a semaphore in memory on the /dev/shm/ directory.
 *
 * @return semaphore
 */
Semaphore CreateSemaphore();

/**
 * @brief Closes the current semaphore instance provided.
 *
 * @param semaphore
 */
void CloseSemaphore(Semaphore *semaphore);

/**
 * @brief Frees from memory the semaphore instance provided from /dev/shm/
 * location.
 *
 * @param semaphore
 */
void FreeSemaphore(Semaphore *semaphore);

/**
 * @brief Does a synchronized call to a given function pointer with a shared
 * memory block to write to memory.
 *
 * @param semaphore
 * @param func
 * @param sharedBlock
 */
void SyncReceiver(Semaphore *semaphore, SyncFunc func,
                  SharedBlock *sharedBlock);

/**
 * @brief Does a synchronized call to a given function pointer with a shared
 * memory block to read from memory.
 *
 * @param semaphore
 * @param func
 * @param sharedBlock
 */
void SyncSender(Semaphore *semaphore, SyncFunc func, SharedBlock *sharedBlock);

#endif  // BLOCK_SEMAPHORE_H