#ifndef ULTRA_TERMINATOR_PARSER_H
#define ULTRA_TERMINATOR_PARSER_H

typedef struct UTermParser {
  char full_line[50];
  char*** arguments;
  unsigned int command_count;
} UTermParser;

void PrintParsedTerminal(UTermParser* parser);

void PopulateParser(UTermParser* parser);

void FreeParser(UTermParser* parser);

char** SplitCommand(char* command);

int CountChar(char* str, char target);

char* Tokenize(char* str, char* delimeter, char** savepoint);

#endif  // ULTRA_TERMINATOR_PARSER_H