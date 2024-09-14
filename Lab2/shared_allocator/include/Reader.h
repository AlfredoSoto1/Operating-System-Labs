#ifndef READER_H
#define READER_H

#define COUNT 1000000
#define SHM_SIZE COUNT * sizeof(int)

typedef struct SharedBlock SharedBlock;

/**
 * @brief Runs a shared memory block to read from it
 *
 */
void RunSharedReader();

/**
 * @brief Reads data into the shared memory block given.
 *
 * @param block
 */
void ReaderSharedData(SharedBlock* block);

/**
 * @brief Runs a memory queue block to read from it
 *
 */
void RunReaderMQ();

#endif  // READER_H