#ifndef WRITER_H
#define WRITER_H

#define COUNT 10
#define SHM_SIZE COUNT * sizeof(long)

void RunWriter();

void WriteData(void* block);

#endif  // WRITER_H