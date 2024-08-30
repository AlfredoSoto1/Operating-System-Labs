#include "TextHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PromptText() {
  printf("Welcome to TextHandler!!\n");

  int line_count;
  int line_length;

  printf("How long do you want your lines to be?\n");
  scanf("%d", &line_length);

  printf("How many lines would you like to have?\n");
  scanf("%d", &line_count);

  printf("Write some text to be justified with %d lines %d characters long.\n",
         line_count, line_length);
  printf("Press 'Enter' to record your text.\n\n\n");

  char* text;

  scanf("%s", &text);

  printf("\n\n%s", text);
}

char* JustLeft(char* text);
char* JustRight(char* text);
char* JustBlock(char* text);