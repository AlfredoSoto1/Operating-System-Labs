#ifndef ULTRA_TERMINATOR_H
#define ULTRA_TERMINATOR_H

void RunUltraTerminator();

UTermParser GetTerminal();

int GetCommandArguments(UTermParser* parser);

int RunProcess(char* program, char** argv);

void WaitForProcess(int process);

#endif  // ULTRA_TERMINATOR_H
