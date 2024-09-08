#ifndef ULTRA_TERMINATOR_H
#define ULTRA_TERMINATOR_H

struct UTermParser;

void RunUltraTerminator();

struct UTermParser GetTerminal();

int RunProcess(char* program, char** argv);

void WaitForProcess(int process);

#endif  // ULTRA_TERMINATOR_H
