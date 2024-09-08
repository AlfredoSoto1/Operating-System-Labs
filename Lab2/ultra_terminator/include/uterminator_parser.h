#ifndef ULTRA_TERMINATOR_PARSER_H
#define ULTRA_TERMINATOR_PARSER_H

typedef struct UTermParser {
  char full_line[50];
  char*** arguments;
  unsigned int command_count;
  unsigned int argument_count;
} UTermParser;

void PopulateParser(UTermParser* parser);

int CountChar(char* str, char target);

#endif  // ULTRA_TERMINATOR_PARSER_H