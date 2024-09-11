#ifndef ULTRA_TERMINATOR_H
#define ULTRA_TERMINATOR_H

/**
 * @note Forward declaration of the parser to be used for the Ultra Terminator
 */
typedef struct UTermParser UTermParser;

/**
 * @brief Runs the Ultra Terminator Program
 */
void RunUltraTerminator();

/**
 * @brief Gets the current terminat state for parsing
 *
 * @return UTermParser
 */
UTermParser GetTerminal();

/**
 * @brief Runs a process with a given program name and arguments
 *
 * @param program
 * @param argv
 *
 * @return process id
 */
int RunProcess(char* program, char** argv);

/**
 * @brief Waits for the given process to finish
 *
 * @param process
 */
void WaitForProcess(int process);

#endif  // ULTRA_TERMINATOR_H
