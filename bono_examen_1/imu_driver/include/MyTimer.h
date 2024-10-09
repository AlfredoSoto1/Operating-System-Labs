#ifndef MY_TIMER_H
#define MY_TIMER_H

#define PERIOD_MS 200

extern double timer_time;
extern int enable_writing_flg;

/**
 * @brief Handles the timer signal every 200ms.
 *
 * @param sig
 */
void HandleTimeSignal(int sig);

/**
 * @brief Creates a new timer that ticks every 200ms.
 *
 */
void PrepareTimer();

#endif  // MY_TIMER_H