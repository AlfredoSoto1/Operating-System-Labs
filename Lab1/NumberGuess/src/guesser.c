#include "guesser.h"

#include <stdio.h>

#define SELECTION_DOMAIN 10  // Number selection domain

int GenerateRandNumber() {
  srand(time(NULL));
  return rand() % SELECTION_DOMAIN + 1;
}

int GetUserGuess() {
  int user_guess;
  printf("Enter number to guess:");
  scanf("%d", &user_guess);
  return user_guess;
}

int VerifyGuess() {
  int tries = SELECTION_DOMAIN;
  int rng = GenerateRandNumber();

  do {
    int guess = GetUserGuess();

    if (rng != guess) {
      printf("Incorrect number guess, try again!\n");
      continue;
    }

    printf("Nice! you guessed the number %d", guess);
    return guess;

  } while (tries-- != 0);

  printf("You ran out of tries!");
  return -1;
}