#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

/**
 * @brief Tells the user to enter some text to apply some justification.
 *
 */
void PromptText();

/**
 * @brief Justifies the text to the left
 *
 * @param text
 * @return char*
 */
char* JustLeft(char* text);

/**
 * @brief Justifies the text to the right
 *
 * @param text
 * @return char*
 */
char* JustRight(char* text);

/**
 * @brief Justifies the text to behave as block
 *
 * @param text
 * @return char*
 */
char* JustBlock(char* text);

#endif  // TEXT_HANDLER_H