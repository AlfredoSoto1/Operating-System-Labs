
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
  int used[DECK_SIZE] = {0};
  int card_count = 0;

  srand(time(NULL));

  while (card_count < 5) {
    int index = rand() % DECK_SIZE;

    // If the card hasn't been used
    if (!used[index]) {
      hand[card_count] = deck[index];

      // Mark card as used
      used[index] = 1;
      card_count++;
    }
  }
}

void evaluate_hand(Card hand[5]) {
  int ranks[13] = {0};
  int suits[4] = {0};

  // Count the occurrences of each rank and suit
  for (int i = 0; i < 5; i++) {
    ranks[hand[i].rank - 2]++;
    suits[hand[i].suit]++;
  }

  // Validate for flush
  for (int i = 0; i < 4; i++) {
    if (suits[i] == 5) {
      printf("Flush found!\n");
      return;
    }
  }

  // Validate for straight
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

static const char* getRank(Rank rank) {
  switch (rank) {
    case TWO:
      return "2";
    case THREE:
      return "3";
    case FOUR:
      return "4";
    case FIVE:
      return "5";
    case SIX:
      return "6";
    case SEVEN:
      return "7";
    case EIGHT:
      return "8";
    case NINE:
      return "9";
    case TEN:
      return "10";
    case JACK:
      return "Jack";
    case QUEEN:
      return "Queen";
    case KING:
      return "King";
    case ACE:
      return "Ace";
  }
}

static const char* getSuits(Suit suit) {
  switch (suit) {
    case HEARTS:
      return "Hearts";
    case DIAMONDS:
      return "Diamonds";
    case CLUBS:
      return "Clubs";
    case SPADES:
      return "Spades";
  }
}

void print_hand(const Card hand[5]) {
  printf("Hand:\n");
  for (int i = 0; i < 5; i++) {
    printf("%s of %s\n", getRank(hand[i].rank), getSuits(hand[i].suit));
  }
  printf("\n");
}