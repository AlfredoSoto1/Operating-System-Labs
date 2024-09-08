#ifndef ULTRA_TERMINATOR_PARSER_H
#define ULTRA_TERMINATOR_PARSER_H

typedef struct UTermParser {
  char full_line[100];  // Max of 100 characters per line for this terminal
  char*** arguments;    // Arguments that the terminal will use to process
  unsigned int command_count;  // Number of commands that will be processed
} UTermParser;

/**
 * @brief Prints to the terminal the Ultra Terminator parser
 *
 * @param parser
 */
void PrintParsedTerminal(UTermParser* parser);

/**
 * @brief Frees from memory all allocated data of the parser
 *
 * @param parser
 */
void FreeParser(UTermParser* parser);

/**
 * @brief Populates the parser struct content
 *
 * @param parser
 */
void PopulateParser(UTermParser* parser);

/**
 * @brief Gets the Command Args object
 *
 * @param str
 * @param endstr
 * @return char** List of arguments
 */
char** GetCommandArgs(char* str, char* endstr);

/**
 * @brief Counts the number of characters from the given string
 *
 * @param str
 * @param endl
 * @param target
 * @return int number of char from target
 */
int CountChar(char* str, char endl, char target);

#endif  // ULTRA_TERMINATOR_PARSER_H