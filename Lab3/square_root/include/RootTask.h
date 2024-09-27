#ifndef ROOT_TASK_H
#define ROOT_TASK_H

typedef struct RootTask {
  unsigned long n_read_values;
  unsigned char* input_buffer;
  unsigned long n_processed_values;
  double* processed_buffer;
} RootTask;

extern RootTask root_task;

/**
 * @brief
 *
 * @param param
 * @return void*
 */
void* BufferHandler(void* param);

/**
 * @brief
 *
 * @param param
 * @return void*
 */
void* ComputeSqrt(void* param);

/**
 * @brief
 *
 * @param param
 * @return void*
 */
void* FileHandlerOutput(void* param);

/**
 * @brief
 *
 */
void RunRootTask();

#endif  // ROOT_TASK_H