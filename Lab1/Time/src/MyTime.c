#include "MyTime.h"

#include <stdio.h>

void PrintTime(const Time* time) {
  printf("%02d:%02d:%02d\n", time->hour, time->minute, time->second);
}

Time GetTime() {
  Time time;

  do {
    printf("Enter hours (0-23): ");
    scanf("%d", &time.hour);
  } while (time.hour < 0 || time.hour > 23);

  do {
    printf("Enter minutes (0-59): ");
    scanf("%d", &time.minute);
  } while (time.minute < 0 || time.minute > 59);

  do {
    printf("Enter seconds (0-59): ");
    scanf("%d", &time.second);
  } while (time.second < 0 || time.second > 59);

  return time;
}