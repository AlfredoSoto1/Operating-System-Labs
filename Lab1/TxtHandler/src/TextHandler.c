#include "TextHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char** CreateParagraphBlock(unsigned int line_count, unsigned int line_length) {
  char** paragraph = (char**)malloc(line_count * sizeof(char*));

  for (int i = 0;i < line_count;i++) {
    paragraph[i] = malloc((line_length + 1) * sizeof(char));
  }

  return paragraph;
}

static void FreeParagraph(char** paragraph, unsigned int line_count) {
  for (unsigned int i = 0; i < line_count; i++) {
    free(paragraph[i]);
  }
  free(paragraph);
}

void PromptText() {
  printf("Welcome to TextHandler!!\n");

  unsigned int line_count;
  unsigned int line_length;

  printf("How long do you want your lines to be?\n");
  scanf("%d", &line_length);

  printf("How many lines would you like to have?\n");
  scanf("%d", &line_count);

  // Empty the last char used
  getchar();

  printf("Write some text to be justified with %d lines %d characters long.\n",
         line_count, line_length);
  printf("Press 'Enter' to record your text.\n\n\n");

  char** paragraph = CreateParagraphBlock(line_count, line_length);

  for (unsigned int i = 0; i < line_count; i++) {
    printf("Line %u: ", i + 1);
    fgets(paragraph[i], line_length + 1, stdin);

    // Reset text input buffer
    getchar();
    
    // Remove newline character if it was read
    paragraph[i][strcspn(paragraph[i], "\n")] = '\0';
  }

  printf("\nYou entered:\n");
  for (unsigned int i = 0; i < line_count; i++) {
    printf("%s\n", paragraph[i]);
  }

  FreeParagraph(paragraph, line_count);
}

char* JustLeft(char* text);
char* JustRight(char* text);
char* JustBlock(char* text);