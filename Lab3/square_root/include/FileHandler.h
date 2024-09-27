#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>

#define LENGTH_OF_FILE 10000

/**
 * @brief
 *
 * @param file
 */
void WriteToFile(FILE* file);

/**
 * @brief
 *
 * @param param
 * @return void*
 */
void* FileHandlerPrepare(void* param);

/**
 * @brief
 *
 */
void BootFileHandler();

#endif  // FILE_HANDLER_H