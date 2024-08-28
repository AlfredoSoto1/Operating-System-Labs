#ifndef MYTIME_H
#define MYTIME_H

/**
 * @brief Holds the values for time
 *
 */
typedef struct Time {
  int hour;
  int minute;
  int second;
} Time;

/**
 * @brief Prints the time struct in the format <hour>:<minutes>:<seconds>
 *
 * @param time
 */
void PrintTime(const Time* time);

/**
 * @brief Get the Time structure
 *
 * @return Time
 */
Time GetTime();

#endif  // MYTIME_H