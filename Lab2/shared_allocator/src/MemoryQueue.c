#include "MemoryQueue.h"

#include <stdlib.h>

Queue CreateMemoryQueue() {
  Queue queue;
  queue.error = 0;

  struct mq_attr attr;

  // Initialize the queue attributes
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = BLOCK_SIZE;
  attr.mq_curmsgs = 0;

  // Create the message queue
  // With permissions of READ-WRITE
  queue.mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
  if (queue.mq == (mqd_t)-1) {
    perror("mq_open");
    queue.error = 1;
    return queue;
  }

  return queue;
}

ssize_t Dequeue(Queue* queue) {
  return mq_receive(queue->mq, queue->buffer, BLOCK_SIZE, NULL);
}

void Enqueue(Queue* queue) {
  // Send with priority of 0 (NONE)
  if (mq_send(queue->mq, queue->buffer, BLOCK_SIZE, 0) == -1) {
    perror("mq_send");
    return;
  }
}

void CloseQueue(Queue* queue) {
  // Close and unlink the message queue
  if (mq_close(queue->mq) == -1) {
    perror("mq_close");
    queue->error = 2;
    return;
  }
}

void FreeQueue(Queue* queue) {
  if (mq_unlink(QUEUE_NAME) == -1) {
    perror("mq_unlink");
    queue->error = 2;
    return;
  }
}