#ifndef ULTRA_TERMINATOR_PARSER_H
#define ULTRA_TERMINATOR_PARSER_H

typedef struct UTermParser {
  char full_line[50];
  char*** arguments;
  unsigned int command_count;
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