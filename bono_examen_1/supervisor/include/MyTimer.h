#ifndef MY_TIMER_H
#define MY_TIMER_H

#define PERIOD_MS 1500  // 1.5s
extern int enable_imu_driver_detection;

/**
 * @brief Handles the timer signal received every 1.5 seconds
 *
 * @param sig
 */
void HandleTimeSignal(int sig);

/**
 * @brief Creates the timer with 1.5 seconds of period
 *
 */
void PrepareTimer();

#endif  // MY_TIMER_H