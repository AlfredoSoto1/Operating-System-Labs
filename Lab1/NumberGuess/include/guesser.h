
/**
 * @brief Generates a random number from a selected domain by the programmer
 *
 * @return int - randomly generated number
 */
int GenerateRandNumber();

/**
 * @brief Reads the console for the user input serving as the user guess
 *
 * @return int - guess from user
 */
int GetUserGuess();

/**
 * @brief Validates the user guess from the randomly generated number
 *
 * @return number guessed correctly, -1 if it failed after N attempts
 */
int VerifyGuess();