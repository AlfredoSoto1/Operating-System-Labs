#include "inf_counter.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int global_counter = 0;
static int direction = 1;  // Increase positively

void HandlerSig1(int sig_num) {
  // Sets the global counte to zero
  global_counter = 0;
}

void HandlerSig2(int sig_num) {
  // Set the direction to the new signal
  // its going to be always inverted
  direction *= -1;
}

void SignalPrepare() {
  struct sigaction sig_1;
  struct sigaction sig_2;

  sig_1.sa_handler = HandlerSig1;
  sig_2.sa_handler = HandlerSig2;

  sigaction(SIGUSR1, &sig_1, NULL);
  sigaction(SIGUSR2, &sig_2, NULL);
}

void UpdateProgramCounter() {
  SignalPrepare();

  while (1) {
    printf("I'm counting, and my count is %d\n", global_counter);

    // Increase the global counter by the set direction
    global_counter += direction;

    // Wait for 1 second
    sleep(1);
  }
}
