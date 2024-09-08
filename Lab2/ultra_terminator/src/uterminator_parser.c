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

void PopulateParser(UTermParser* parser) {
  // Count the ammount of commands are in the line
  parser->command_count = CountChar(parser->full_line, ';') + 1;

  // Reserve space for each command
  parser->arguments = (char***)malloc(parser->command_count * sizeof(char**));

  // Duplicate the full_line to work with each token as a single command string
  int command_index = 0;
  char* savepoint;
  char* line_copy = strdup(parser->full_line);
  char* command = Tokenize(line_copy, ";", &savepoint);

  // Iterate over each command to obtain its arguments
  while (command != NULL) {
    printf("test command: %s\n", command);
    parser->arguments[command_index++] = SplitCommand(command);
    command = Tokenize(NULL, ";", &savepoint);
  }

  free(line_copy);
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

char** SplitCommand(char* command) {
  // Set the number of arguments
  int argc = CountChar(command, ' ') + 1;

  // Allocate space for each argument inside the command
  char** line_args = (char**)malloc(argc * sizeof(char*));

  int letter_index = 0;
  char* command_copy = strdup(command);
  char* argument = strtok(command_copy, " \t");

  while (argument != NULL) {
    if (*argument == '\n') continue;

    // Copy the argument into the argument list. This creates a new allocation
    // that has to be handled later.
    line_args[letter_index++] = strdup(argument);
    argument = strtok(NULL, " \t");
  }

  line_args[letter_index] = NULL;
  free(command_copy);

  return line_args;
}

int CountChar(char* str, char target) {
  int count = 0;
  while (*str != '\0') {
    // If character is found, increase the count
    if (*str == target) count++;
    str++;
  }
  return count;
}

char* Tokenize(char* str, char* delimeter, char** savepoint) {
  char* token;

  // This will set up the savepoint for the first call
  if (str != NULL) {
    *savepoint = str;
  }

  // Jump to the next savepoint which is right after the first delimeter
  *savepoint += strspn(*savepoint, delimeter);

  // Check if it has reached the end
  if (**savepoint == '\0') return NULL;

  // Token will start at the savepoint
  token = *savepoint;

  return token;
}