#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int SpawnChildren(const char* program) {
  // Create a new child
  int child_pid = fork();

  // Leave the rest of the function to the child
  if (child_pid != 0) {
    return child_pid;
  }

  // Print the program id of the child
  printf("I'm a child, and my id is: %d\n", getpid());

  // Create the first greetings grandson
  int grand_son1_err;
  int grand_son1 = fork();

  if (grand_son1 == 0) {
    // Transform process into Greetings program
    execlp(program, "greetings_process", NULL);

    // Exit with parent with failure if exec() fails
    exit(EXIT_FAILURE);
  }

  // Create the second greetings grandson
  int grand_son2_err;
  int grand_son2 = fork();

  if (grand_son2 == 0) {
    // Transform process into Greetings program
    execlp(program, "greetings_process", NULL);

    // Exit with parent with failure if exec() fails
    exit(EXIT_FAILURE);
  }

  // Wait for both grandsons
  waitpid(grand_son1, &grand_son1_err, 0);
  waitpid(grand_son2, &grand_son2_err, 0);

  // The children ends successfully
  exit(EXIT_SUCCESS);

  // This return should never happen
  return -1;
}

void WaitForChildren(int* processes, const unsigned int process_count) {
  if (process_count == 0 || processes == NULL) return;

  int process_status[process_count];

  for (int i = 0; i < process_count; i++) {
    // Wait for each process to finish
    // Store the exit status to the process_status array
    waitpid(processes[i], &process_status[i], 0);
  }

  // Log information to the console
  // printf("All processses have finished\n");

  for (int i = 0; i < process_count; i++) {
    printf("Process child [%d] exited with: %d\n", processes[i],
           WEXITSTATUS(process_status[i]));
  }
}
