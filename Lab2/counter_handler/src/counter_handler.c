#include "counter_handler.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

MenuSelection DisplayMenu() {
  do {
    printf("-----------------------------------------\n");
    printf("Select what to do with all the processes:\n");

    printf("1. Stop\n");
    printf("2. Continue\n");
    printf("3. Change direction\n");
    printf("4. Kill\n");

    int selection;
    scanf("%d", &selection);

    if (selection < 1 || selection > 4) {
      printf("Invalid option try again.\n");
      continue;
    }

    return selection;
  } while (1);
}

int HandleProcessSelection(InputArguments* arguments) {
  // Validation flag to escape selection
  int validated = 0;
  int process_selected = -1;

  do {
    printf("----------------------------------\n");
    printf("Which process do you want to stop?\n");

    for (int i = 0; i < arguments->count; i++) {
      printf("%d, ", arguments->program_ids[i]);
    }
    printf("\n");

    int process_selection;
    scanf("%d", &process_selection);

    for (int i = 0; i < arguments->count; i++) {
      // Validate pid selected
      if (process_selection == arguments->program_ids[i]) {
        validated = 1;
        process_selected = arguments->program_ids[i];
        break;
      }
    }

    // Print warning message
    if (!validated)
      printf("Process is not in selection menu. Please select again.\n");

  } while (!validated);

  return process_selected;
}

void HandleStopSelection(InputArguments* arguments) {
  int process_selected = HandleProcessSelection(arguments);

  // Send signal
  kill(process_selected, SIGSTOP);
}

void HandleContinueSelection(InputArguments* arguments) {
  int process_selected = HandleProcessSelection(arguments);

  // Send signal
  kill(process_selected, SIGCONT);
}

void HandleChangeSelection(InputArguments* arguments) {
  int process_selected = HandleProcessSelection(arguments);

  // Send signal
  kill(process_selected, SIGUSR2);
}

void HandleKillSelection(InputArguments* arguments) {
  int process_selected = HandleProcessSelection(arguments);

  // Send signal
  kill(process_selected, SIGKILL);
}

int AtleastOneAlive(InputArguments* arguments) {
  // Check if atleast one process is still alive
  int process_alive = 0;
  for (int i = 0; i < arguments->count; i++) {
    if (kill(arguments->program_ids[i], 0) == 0) {
      process_alive++;
    }
  }

  // If there is no process alive it will return false -> 0
  return process_alive != 0;
}