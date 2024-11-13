#ifndef PLOTTING_H
#define PLOTTING_H

#define PAGE_SIZE sizeof(int) * 1000

// Pointer that holds data to plot.
// Only avaliable for the current translation unit (c - file)
static int* plotting_block;

/**
 * @brief Prints the data every 2.2 seconds after a heads up to 1.9s after.
 *
 * @param sig
 */
void PrintData(int sig);

/**
 * @brief Prepares the timer configuration
 *
 */
void PrepareTimer();

/**
 * @brief Reads data from input from user.
 *
 * @return NULL
 */
void* ReadData(void*);

/**
 * @brief Runs the tests for plotting
 *
 */
void RunTest();

#endif  // PLOTTING_H