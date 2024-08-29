#include "NumberLib.h"

#include <stdio.h>

int main() {
  char* string1 = NumToStr(11528);
  char* string2 = NumToStr(765);
  char* string3 = NumToStr(12368);
  char* string4 = NumToStr(123);
  char* string5 = NumToStr(0);

  printf("%s\n", string1);
  printf("%s\n", string2);
  printf("%s\n", string3);
  printf("%s\n", string4);
  printf("%s\n", string5);

  free(string1);
  free(string2);
  free(string3);
  free(string4);
  free(string5);
  return 0;
}