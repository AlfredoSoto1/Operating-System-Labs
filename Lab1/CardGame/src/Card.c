
#include "Card.h"

#include <stdio.h>

void fill_deck(Card deck[DECK_SIZE]) {
  int i = 0;
  for (Suit s = HEARTS; s <= SPADES; s++) {
    for (Rank r = ACE; r <= KING; r++) {
      deck[i].suit = s;
      deck[i].rank = r;
      i++;
    }
  }
}

void fill_hand(Card hand[5], Card deck[DECK_SIZE]) {
  int used[DECK_SIZE] = {0};  // Array to track used cards
  int card_count = 0;

  while (card_count < 5) {
    srand(time(NULL));
    int index = rand() % DECK_SIZE;

    if (!used[index]) {                // If the card hasn't been used
      hand[card_count] = deck[index];  // Copy card to hand
      used[index] = 1;                 // Mark card as used
      card_count++;
    }
  }
}