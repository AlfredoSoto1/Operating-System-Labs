#ifndef MEMORY_QUEUE_H
#define MEMORY_QUEUE_H

#include <mqueue.h>

#define BLOCK_SIZE sizeof(int)

#define COUNT_STOP 1000000
#define QUEUE_NAME "/test_queue"

/**
 * @brief Queue structure
 *
 */
typedef struct Queue {
  mqd_t mq;
  char buffer[BLOCK_SIZE];
  ssize_t bytes_read;
  int error;
} Queue;

/**
 * @brief Creates a new block of memory to behave as a queue.
 *
 * @return queue
 */
Queue CreateMemoryQueue();

/**
 * @brief Receives the data from the buffer in the queue instance provided.
 *
 * @param queue
 * @return size of the block that read
 */
ssize_t Dequeue(Queue* queue);

/**
 * @brief Sends to the queue the data from the buffer in the queue instance
 * provided.
 *
 * @param queue
 */
void Enqueue(Queue* queue);

/**
 * @brief Closes the current instance of the queue provided.
 *
 * @param queue
 */
void CloseQueue(Queue* queue);

/**
 * @brief Frees from memory the queue instance provided located at /dev/mqueue/
 * location.
 *
 * @param queue
 */
void FreeQueue(Queue* queue);

#endif  // MEMORY_QUEUE_H