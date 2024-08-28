#ifndef CARD_H
#define CARD_H

#define DECK_SIZE 52

/**
 * @brief Representation of a Suit as an enum
 */
typedef enum Suit {
  HEARTS,
  DIAMONDS,
  CLUBS,
  SPADES,
} Suit;

/**
 * @brief Representation of the Rank as an enum
 */
typedef enum Rank {
  TWO = 2,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING,
  ACE
} Rank;

/**
 * @brief Representation of a single card object-struct
 *
 */
typedef struct Card {
  Suit suit;
  Rank rank;
} Card;

/**
 * @brief Fills the given card deck pointer
 *
 * @param deck Pointer to the array of 52 cards
 */
void fill_deck(Card deck[DECK_SIZE]);

/**
 * @brief Fills the hand using a given deck
 *
 * @param hand Pointer to the array of 5 cards representing the hand.
 * @param deck Pointer to the array of 52 cards.
 */
void fill_hand(Card hand[5], Card deck[DECK_SIZE]);

/**
 * @brief Evaluates if the given hand is one of the following:
 *
 * @brief - Pair
 * @brief - Two pairs
 * @brief - Three of a kind
 * @brief - Flush
 * @brief - Straight
 * @brief - Four of a kind
 *
 * @param hand Pointer to the array of 5 cards representing the hand.
 */
void evaluate_hand(Card hand[5]);

/**
 * @brief Prints the hand
 *
 * @param hand Pointer to the array of 5 cards representing the hand.
 */
void print_hand(const Card hand[5]);

#endif  // CARD_H