#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROGRAM_LIFETIME 10  // Seconds

int main() {
  // Print the welcome message
  printf("hello there, I'm program %d\n", getpid());

  int time_seconds = 0;
  clock_t start = clock();

  int iterations = 0;

  do {
    // Obtains the time in miliseconds
    clock_t difference = clock() - start;
    time_seconds = difference;  // * 1000 / CLOCKS_PER_SEC;

    if (difference % 1000 == 0) printf("%d\n", time_seconds);

    iterations++;
  } while (time_seconds < 10 * 10000);

  // Print exit farewell
  printf("I'm done, bye!\n");

  return 0;
}