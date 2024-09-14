#ifndef WRITER_H
#define WRITER_H

#define COUNT 1000000
#define SHM_SIZE COUNT * sizeof(int)

void RunWriter();

void WriteData(void* block);

#endif  // WRITER_H