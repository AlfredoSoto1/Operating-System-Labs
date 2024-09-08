#include "ultra_terminator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <sys/wait.h>
// #include <unistd.h>

#include "uterminator_parser.h"

static void ClearInBuffer() {
  char ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}

void RunUltraTerminator() {
  do {
    // Get the latest input from terminal
    UTermParser parser = GetTerminal();

    // Parse the input from terminal
    PopulateParser(&parser);

    for (unsigned int i = 0; i < parser.command_count; i++) {
      char** args = parser.arguments[i];

      // If the first argument is not there, skip it
      if (args[0] == NULL) continue;

      // Run a new process
      int processid = RunProcess(parser.arguments[i][0], args);

      // Wait for the process to end
      WaitForProcess(processid);
    }

    // Free the parsed data allocated
    FreeParser(&parser);
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

int RunProcess(char* program, char** argv) {
  // Create a new child
  int child_pid = 0;  // fork();

  // Leave the rest of the function to the child
  if (child_pid != 0) {
    return child_pid;
  }

  // Transform process into Greetings program
  // execvp(program, argv);

  // Failed running the program
  return -1;
}

void WaitForProcess(int process) {
  int process_status;
  // Wait for the process to finish
  // Store the exit status to the process_status variable
  // waitpid(process, &process_status, 0);

  // Use later if necesary
  // WEXITSTATUS(process_status[i])
}
