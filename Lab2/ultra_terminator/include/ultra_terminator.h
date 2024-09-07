#ifndef ULTRA_TERMINATOR_H
#define ULTRA_TERMINATOR_H

#define MAX_COMMANDS 10
#define MAX_ARGUMENTS 5

typedef struct UTermParser {
  char full_line[50];
  char* command[MAX_COMMANDS];
  char** arguments[MAX_ARGUMENTS];
} UTermParser;

void RunUltraTerminator();

UTermParser GetTerminal();

int GetCommands(UTermParser* term);

int GetCommandArguments(UTermParser* parser);

int RunProcess(char* program, char** argv);

void WaitForProcess(int process);

#endif  // ULTRA_TERMINATOR_H
