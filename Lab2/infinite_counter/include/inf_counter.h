#ifndef INF_COUNTER_H
#define INF_COUNTER_H

/**
 * @brief Handles the user signal 1
 *
 * @param sig_num
 */
void HandlerSig1(int sig_num);

/**
 * @brief Handles the user signal 2
 *
 * @param sig_num
 */
void HandlerSig2(int sig_num);

/**
 * @brief Updates the program counter
 */
void UpdateProgramCounter();

#endif  // INF_COUNTER_H