#include "StringLib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Replace(char* src, char* dst, char find, char replacement) {
  size_t length = strlen(src);

  dst = (char*)malloc((length + 1) * sizeof(char));

  if (*dst == NULL) {
    printf("Memory allocation failed.\n");
    return;
  }

  // Replace the characters
  for (size_t i = 0; i < length; ++i) {
    if (src[i] == find) {
      dst[i] = replacement;
    } else {
      dst[i] = src[i];
    }
  }

  // Null-terminate the destination string
  dst[length] = '\0';
}

void Insert(char* src, char* dst, char find, char* ins) {}