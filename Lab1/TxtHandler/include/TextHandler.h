#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

/**
 * @brief Paragraph structure containing the main text and information about it
 *
 */
typedef struct Paragraph {
  char** text;
  unsigned int line_count;
  unsigned int line_length;
} Paragraph;

/**
 * @brief Prints the paragraph given
 *
 * @param paragraph
 */
void PrintParagraph(Paragraph* paragraph);

/**
 * @brief Frees the allocated paragraph memory
 *
 * @param paragraph
 */
void FreeParagraph(Paragraph* paragraph);

/**
 * @brief Tells the user to enter some text to apply some justification
 *
 * @return Paragraph
 */
Paragraph PromptTextProgram();

/**
 * @brief Justifies the text to the left
 *
 * @param paragraph*
 */
void JustLeft(Paragraph* paragraph);

/**
 * @brief Justifies the text to the right
 *
 * @param paragraph*
 */
void JustRight(Paragraph* paragraph);

/**
 * @brief Justifies the text to behave as block
 *
 * @param paragraph*
 */
void JustBlock(Paragraph* paragraph);

#endif  // TEXT_HANDLER_H