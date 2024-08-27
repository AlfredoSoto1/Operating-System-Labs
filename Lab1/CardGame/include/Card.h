
#define DECK_SIZE 52

/**
 * @brief Card Suit
 */
typedef enum Suit {
  HEARTS,
  DIAMONDS,
  CLUBS,
  SPADES,
} Suit;

/**
 * @brief Card Rank
 */
typedef enum Rank {
  ACE = 1,
  TWO,
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
  KING
} Rank;

/**
 * @brief Card
 */
typedef struct Card {
  Suit suit;
  Rank rank;
} Card;

/**
 * @brief
 *
 */
void fill_deck();

/**
 * @brief
 *
 */
void fill_hand(Card hand[5], Card deck[DECK_SIZE]);