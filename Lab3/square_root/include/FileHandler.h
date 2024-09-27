#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>

#define LENGTH_OF_FILE 10000

/**
 * @brief Writes to the numbers.txt file a set of random numbers from [0, 255]
 *
 * @param file
 */
void WriteToFile(FILE* file);

/**
 * @brief Prepares the file creation if not existant previously
 *
 * @param param
 * @return void*
 */
void* FileHandlerPrepare(void* param);

/**
 * @brief Kicks off thread to run this when application boots
 *
 */
void BootFileHandler();

#endif  // FILE_HANDLER_H