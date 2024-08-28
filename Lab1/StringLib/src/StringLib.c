#include "StringLib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Replace(char* src, char* dst, char find, char replacement) {
  size_t length = strlen(src);

  // Replace the characters
  for (size_t i = 0; i < length; i++) {
    if (src[i] == find) {
      dst[i] = replacement;
    } else {
      dst[i] = src[i];
    }
  }

  // Null-terminate the destination string
  dst[length] = '\0';
}

void Insert(char* src, char* dst, char find, char* ins) {
  size_t length = strlen(src);
  size_t insert_length = strlen(ins);

  size_t new_word_index = 0;
  int replace_count = 0;

  // Find the characters
  for (size_t i = 0; i < length; i++) {
    // Copy what we have currently
    if (src[i] != find) {
      dst[new_word_index++] = src[i];
      continue;
    }

    replace_count++;

    // Copy the last character before inserting
    dst[new_word_index++] = src[i];

    // Insert the new word into the string
    for (size_t ins_index = 0; ins_index < insert_length; ins_index++) {
      dst[new_word_index++] = ins[ins_index];
    }
  }

  // Null-terminate the destination string
  dst[length + insert_length * replace_count] = '\0';
}