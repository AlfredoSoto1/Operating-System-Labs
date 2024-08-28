#include "StringLib.h"

void test1() {
  const char* original_str = "hola mundo";
  char find_char = 'o';
  char replacement_char = 'a';

  char* replaced_str = (char*)malloc(MAX_LENGTH);
  // Replace function usage
  Replace(original_str, replaced_str, find_char, replacement_char);

  printf("Replaced String: %s\n", replaced_str);
  free(replaced_str);
}

void test2() {
  const char* original_str = "hola mundo";
  char find_char = 'o';
  char* replacement_str = "ronda";

  char* inserted_str = (char*)malloc(MAX_LENGTH);
  // Insert function usage
  Insert(original_str, inserted_str, find_char, replacement_str);

  printf("Inserted String: %s\n", inserted_str);
  free(inserted_str);
}

int main() {
  test1();
  test2();

  return 0;
}