#include "uterminator_parser.h"

void PopulateParser(UTermParser* parser) {
  // Count the ammount of commands are in the line
  parser->command_count = CountChar(parser->full_line, ';') + 1;

  parser->arguments = malloc();
}

int CountChar(char* str, char target) {
  int count = 0;
  while (*str != '\0') {
    // If character is found, increase the count
    if (*str == target) count++;
    // Go forward
    str++;
  }
  return count;
}