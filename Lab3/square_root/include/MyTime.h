#ifndef MY_TIME_H
#define MY_TIME_H

/**
 * @brief Defines the time metric value
 */
typedef long long MyTime;

/**
 * @brief Obtains the current time in milliseconds of the computer state.
 *
 * @return MyTime
 */
MyTime CurrentTimeMillis();

#endif  // MY_TIME_H