#ifndef BLOCK_SEMAPHORE_H
#define BLOCK_SEMAPHORE_H

#include <semaphore.h>

#define SEM_PRODUCER "/producer"
#define SEM_CONSUMER "/consumer"

typedef void (*SyncFunc)(void *);

/**
 * @brief
 */
typedef struct Semaphore {
  sem_t *producer;
  sem_t *consumer;
  int error;
} Semaphore;

/**
 * @brief
 *
 * @return semaphore
 */
Semaphore CreateSemaphore();

/**
 * @brief
 *
 * @param semaphore
 */
void CloseSemaphore(Semaphore *semaphore);

/**
 * @brief
 *
 * @param semaphore
 * @param func
 */
void SyncReceiver(Semaphore *semaphore, SyncFunc func, void *sharedBlock);

/**
 * @brief
 *
 * @param semaphore
 * @param func
 */
void SyncSender(Semaphore *semaphore, SyncFunc func, void *sharedBlock);

#endif  // BLOCK_SEMAPHORE_H