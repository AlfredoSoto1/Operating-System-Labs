#include "Card.h"

int main() {
  Card hand[5];
  Card deck[DECK_SIZE];

  fill_deck(deck);
  fill_hand(hand, deck);

    return 0;
}