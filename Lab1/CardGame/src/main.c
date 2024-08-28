#include "Card.h"

int main() {
  Card hand[5];
  Card deck[DECK_SIZE];

  fill_deck(deck);
  fill_hand(hand, deck);

  printf("Hand:\n");
  print_hand(hand);

  evaluate_hand(hand);

  return 0;
}