#ifndef READER_H
#define READER_H

#define COUNT 1000000
#define SHM_SIZE COUNT * sizeof(int)

void RunReader();

void ReadData(void* block);

#endif  // READER_H