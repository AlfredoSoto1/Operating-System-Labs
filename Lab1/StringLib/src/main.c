#include "StringLib.h"

int main() {
  char* replaced_str;
  char* inserted_str;

  const char* original_str = "hello world";
  char find_char = 'o';
  char replacement_char = '0';
  const char* insert_str = "123";

  // Replace function usage
  Replace(original_str, &replaced_str, find_char, replacement_char);

  printf("Replaced String: %s\n", replaced_str);

  free(replaced_str);  // Don't forget to free the allocated memory
  return 0;
}