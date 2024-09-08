#include "uterminator_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintParsedTerminal(UTermParser* parser) {
  for (int i = 0; i < parser->command_count; i++) {
    printf("-------------\n");
    printf("Command: \n");

    int arg = 0;
    while (parser->arguments[i][arg] != NULL) {
      printf("Argument: %s\n", parser->arguments[i][arg++]);
    }
  }
}

void FreeParser(UTermParser* parser) {
  for (int i = 0; i < parser->command_count; i++) {
    int argument = 0;
    while (parser->arguments[i][argument] != NULL) {
      // Free each argument
      free(parser->arguments[i][argument++]);
    }
    // Free each array of arguments
    free(parser->arguments[i]);
  }
  // Free all the commands
  free(parser->arguments);
}

void print_sub(char* start, char* end) {
  while (start < end) {
    putchar(*start);
    start++;
  }
  putchar('\n');
}

void PopulateParser(UTermParser* parser) {
  // Count the ammount of commands are in the line
  parser->command_count = CountChar(parser->full_line, NULL, ';') + 1;

  // Reserve space for each command
  parser->arguments = (char***)malloc(parser->command_count * sizeof(char**));

  char* start = parser->full_line;
  char* endl = start;
  int command_index = 0;

  do {
    // Move the end pointer to each ';' to complete a command
    while (*endl != ';' && *endl != '\0') {
      endl++;
    }

    // Obtain the command arguments
    parser->arguments[command_index++] = SetCommandArgs(start, endl);

    // Exit after scanning all commands
    if (*endl == '\0') break;

    // Go to the next command
    start = ++endl;

  } while (1);
}

char** SetCommandArgs(char* str, char* endstr) {
  // Set the number of arguments
  int argc = CountChar(str, ';', ' ') + 1;

  // Allocate space for each argument inside the command
  char** line_args = (char**)malloc((argc + 1) * sizeof(char*));

  int letter_index = 0;
  char* begin = str;
  char* last = begin;

  do {
    while (*last != ' ') {
      last++;
    }
    line_args[letter_index] = (char*)malloc((last - str + 1) * sizeof(char));

    memcpy(line_args[letter_index], str, last - str);

    // Set terminating char of the argument
    line_args[letter_index][last - str] = '\0';

    letter_index++;

    begin = ++last;
  } while (last != endstr);

  // Set the end of the list of arguments
  line_args[letter_index] = NULL;

  return line_args;
}

int CountChar(char* str, char endl, char target) {
  int count = 0;
  while (*str != endl && *str != '\0') {
    // If character is found, increase the count
    if (*str == target) count++;
    str++;
  }
  return count;
}