#include "BlockSemaphore.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "SharedBlock.h"

Semaphore CreateSemaphore() {
  Semaphore semaphore;

  // Set no error for creation
  semaphore.error = 0;

  // Open a semaphore if it exists already with rwx permisions
  semaphore.producer = sem_open(SEM_PRODUCER, O_CREAT, 0666, 0);
  if (semaphore.producer == SEM_FAILED) {
    perror("error opening producer semaphore");
    semaphore.error = 1;
    return semaphore;
  }

  // Open a semaphore if it exists already with rwx permisions
  semaphore.consumer = sem_open(SEM_CONSUMER, O_CREAT, 0666, 1);
  if (semaphore.consumer == SEM_FAILED) {
    perror("error opening consumer semaphore");
    semaphore.error = 2;
    return semaphore;
  }

  return semaphore;
}

void CloseSemaphore(Semaphore *semaphore) {
  sem_close(semaphore->consumer);
  sem_close(semaphore->producer);
}

void FreeSemaphore(Semaphore *semaphore) {
  sem_unlink(SEM_PRODUCER);
  sem_unlink(SEM_CONSUMER);
}

void SyncReceiver(Semaphore *semaphore, SyncFunc func, SharedBlock *block) {
  // Wait for the consumer to allow producer to continue
  sem_wait(semaphore->producer);
  // Run the function
  func(block);
  // Tell the consumer to continue
  sem_post(semaphore->consumer);
}

void SyncSender(Semaphore *semaphore, SyncFunc func, SharedBlock *block) {
  // Wait for the producer to allow consumer to continue
  sem_wait(semaphore->consumer);
  // Run the function
  func(block);
  // Tell the producer to continue
  sem_post(semaphore->producer);
}