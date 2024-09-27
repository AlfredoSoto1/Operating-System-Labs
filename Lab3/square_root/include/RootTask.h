#ifndef ROOT_TASK_H
#define ROOT_TASK_H

/**
 * @brief Holds a reference to the input buffer and processed buffer
 *
 */
typedef struct RootTask {
  unsigned long n_read_values;
  unsigned char* input_buffer;
  unsigned long n_processed_values;
  double* processed_buffer;
} RootTask;

extern RootTask root_task;

/**
 * @brief Handles the buffer on a different thread. Reading the content from the
 * numbers.txt
 *
 * @param param
 * @return void*
 */
void* BufferHandler(void* param);

/**
 * @brief Computes the Sqrt on the numbers handled by the buffer concurrently.
 *
 * @param param
 * @return void*
 */
void* ComputeSqrt(void* param);

/**
 * @brief Outputs the results to a file right after the sub-results are done
 * concurrently.
 *
 * @param param
 * @return void*
 */
void* FileHandlerOutput(void* param);

/**
 * @brief Kicks off the main 3 threads running each of the functions
 * synchronously
 *
 */
void RunRootTask();

#endif  // ROOT_TASK_H