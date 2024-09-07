#include "ultra_terminator.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define COMMAND_SEPARATION ";"
#define COMMAND_ARGUMENT_SEPARATION " "

static void ClearInBuffer() {
  char ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}

void RunUltraTerminator() {
  do {
    // Get the latest input from terminal
    UTermParser parser = GetTerminal();

    GetCommands(&parser);

  } while (1);
}

UTermParser GetTerminal() {
  // Read user input to the terminal to respond
  printf("ultra_terminator > ");

  UTermParser parser;
  fgets(parser.full_line, sizeof(parser.full_line), stdin);

  if (parser.full_line[strlen(parser.full_line) - 1] != '\n') {
    printf("ultra_terminator > Command entered is too long.\n");
    ClearInBuffer();
  }

  // Assign to the last new line to be the end of the string
  parser.full_line[strcspn(parser.full_line, "\n")] = '\0';

  return parser;
  // char* args[] = {"ls", "-la", NULL};
  // int status = RunProcess(command, args);
  // printf("Status: %d\n", status);
}

int CountChar(char* str, char target) {
  int count;
  while (*str != '\0') {
    // If character is found, increase the count
    if (*str == target) count++;
    // Go forward
    str++;
  }
  return count;
}

int GetCommands(UTermParser* parser) {
  int count = 0;

  for (int i = 0; i < strlen(parser->full_line); i++) {
    if (count >= MAX_COMMANDS) {
      printf("ultra_terminator > Too many commands entered (try less than %d)",
             MAX_COMMANDS);
      return -1;
    }

    // Obtain each individual locaiton of where each command ends
    if (parser->full_line[i] == ';') {
      parser->command[count++] = &parser->full_line[i];
    }
  }

  // Set last to be null to end array
  parser->command[count] = NULL;

  return 0;
}

int GetCommandArguments(UTermParser* parser) {
  int count = 0;

  for (int i = 0; i < strlen(parser->full_line); i++) {
    if (count >= MAX_ARGUMENTS) {
      printf(
          "ultra_terminator > Too many arguments per command entered (try less "
          "than %d)",
          MAX_ARGUMENTS);
      return -1;
    }

    // Obtain each individual locaiton of where each command ends
    if (parser->full_line[i] == ';') {
      parser->command[count++] = &parser->full_line[i];
    }
  }

  // Set last to be null to end array
  parser->command[count] = NULL;

  return 0;
}

int RunProcess(char* program, char** argv) {
  // Create a new child
  int child_pid = fork();

  // Leave the rest of the function to the child
  if (child_pid != 0) {
    return child_pid;
  }

  // Transform process into Greetings program
  execvp(program, argv);

  // Failed running the program
  return -1;
}

void WaitForProcess(int process) {
  int process_status;
  // Wait for the process to finish
  // Store the exit status to the process_status variable
  waitpid(process, &process_status, 0);

  // Use later if necesary
  // WEXITSTATUS(process_status[i])
}
