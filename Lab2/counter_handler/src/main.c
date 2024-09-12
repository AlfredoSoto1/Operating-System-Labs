#include "counter_handler.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("At least one process should be given as parameter\n");
    return -1;
  }

  InputArguments arguments;

  // Allocate and set the processes id into the list of ids
  arguments.count = argc - 1;
  arguments.program_ids = malloc(arguments.count * sizeof(int));

  for (int i = 0; i < arguments.count; i++) {
    arguments.program_ids[i] = atoi(argv[i + 1]);
  }

  do {
    // Check if there is atleast one process alive. If not,
    // exit program
    if (!AtleastOneAlive(&arguments)) {
      printf(
          "All registered processes are dead. Program will end "
          "now.\n");
      return 0;
    }

    // If there is atleast one process alive, continue displaying options
    MenuSelection selection = DisplayMenu();

    switch (selection) {
      case STOP:
        HandleStopSelection(&arguments);
        break;
      case CONTINUE:
        HandleContinueSelection(&arguments);
        break;
      case CHANGE:
        HandleChangeSelection(&arguments);
        break;
      case KILL:
        HandleKillSelection(&arguments);
        break;
      default:
        return 0;  // Exit program
    }

  } while (1);

  return 0;
}