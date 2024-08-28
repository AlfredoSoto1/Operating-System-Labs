
#include "Card.h"

#include <stdio.h>
#include <time.h>

void fill_deck(Card deck[DECK_SIZE]) {
  int i = 0;
  for (Suit s = HEARTS; s <= SPADES; s++) {
    for (Rank r = TWO; r <= ACE; r++) {
      deck[i].suit = s;
      deck[i].rank = r;
      i++;
    }
  }
}

void fill_hand(Card hand[5], Card deck[DECK_SIZE]) {
  int used[DECK_SIZE] = {0};  // Array to track used cards
  int card_count = 0;

  srand(time(NULL));

  while (card_count < 5) {
    int index = rand() % DECK_SIZE;

    if (!used[index]) {                // If the card hasn't been used
      hand[card_count] = deck[index];  // Copy card to hand
      used[index] = 1;                 // Mark card as used
      card_count++;
    }
  }
}

void evaluate_hand(Card hand[5]) {
  int ranks[13] = {0};  // Array to count occurrences of each rank
  int suits[4] = {0};   // Array to count occurrences of each suit

  // Count the occurrences of each rank and suit
  for (int i = 0; i < 5; i++) {
    ranks[hand[i].rank - 2]++;
    suits[hand[i].suit]++;
  }

  // Check for flush (all cards of the same suit)
  for (int i = 0; i < 4; i++) {
    if (suits[i] == 5) {
      printf("Flush found!\n");
      return;
    }
  }

  // Check for straight (consecutive ranks)
  for (int i = 0; i <= 8; i++) {
    if (ranks[i] && ranks[i + 1] && ranks[i + 2] && ranks[i + 3] &&
        ranks[i + 4]) {
      printf("Straight found!\n");
      return;
    }
  }

  // Check for pairs, three of a kind, and four of a kind
  int pairs = 0, three_of_a_kind = 0, four_of_a_kind = 0;
  for (int i = 0; i < 13; i++) {
    if (ranks[i] == 2) pairs++;
    if (ranks[i] == 3) three_of_a_kind = 1;
    if (ranks[i] == 4) four_of_a_kind = 1;
  }

  if (four_of_a_kind) {
    printf("Four of a Kind found!\n");
  } else if (three_of_a_kind && pairs) {
    printf("Full House found!\n");
  } else if (three_of_a_kind) {
    printf("Three of a Kind found!\n");
  } else if (pairs == 2) {
    printf("Two Pairs found!\n");
  } else if (pairs == 1) {
    printf("Pair found!\n");
  } else {
    printf("No significant combination found.\n");
  }
}

void print_hand(const Card hand[5]) {
  const char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
  const char *ranks[] = {"2", "3",  "4",    "5",     "6",    "7",  "8",
                         "9", "10", "Jack", "Queen", "King", "Ace"};

  for (int i = 0; i < 5; i++) {
    printf("%s of %s\n", ranks[hand[i].rank - 2], suits[hand[i].suit]);
  }
  printf("\n");
}