#ifndef WRITER_H
#define WRITER_H

#define COUNT 1000000
#define SHM_SIZE COUNT * sizeof(int)

typedef struct SharedBlock SharedBlock;

/**
 * @brief Runs a shared memory block to write to it
 *
 */
void RunSharedWriter();

/**
 * @brief Writes data into the shared memory block given.
 *
 * @param block
 */
void WriteSharedData(SharedBlock* block);

/**
 * @brief Runs a memory queue block to write to it
 *
 */
void RunWriterMQ();

#endif  // WRITER_H