#include <stdio.h>
#include <time.h>

void PrintGreetings() {
  // Prints Greetings message with the process id
  printf("hello there, I'm process %d\n", getpid());

  // Sleep for 10 seconds
  sleep(10);
}

void PrintByeMessage() {
  // Print exit farewell
  printf("I'm done, bye!\n");
}