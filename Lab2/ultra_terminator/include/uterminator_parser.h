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

char** SetCommandArgs(char* str, char* endstr);

int CountChar(char* str, char endl, char target);

#endif  // ULTRA_TERMINATOR_PARSER_H