#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>

/**
 * @brief
 *
 * @param file
 */
void WriteToFile(FILE* file);

/**
 * @brief
 *
 */
void ReadFromFile();

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