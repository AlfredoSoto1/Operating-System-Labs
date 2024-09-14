#ifndef READER_H
#define READER_H

#define COUNT 10
#define SHM_SIZE COUNT * sizeof(long)

void RunReader();

void ReadData(void* block);

#endif  // READER_H