#include "TextHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void CreateParagraphBlock(Paragraph* paragraph) {
  paragraph->text = (char**)malloc(paragraph->line_count * sizeof(char*));

  for (int i = 0;i < paragraph->line_count;i++)
    paragraph->text[i] = malloc((paragraph->line_length + 1) * sizeof(char));
}

static void CleanLineBuffer() {
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}

void FreeParagraph(Paragraph* paragraph) {
  for (unsigned int i = 0; i < paragraph->line_count; i++) {
    free(paragraph->text[i]);
  }
  free(paragraph->text);
}

void PrintParagraph(Paragraph* paragraph) {
  for (int i = 0; i < paragraph->line_count; i++) {
    printf("%s\n", paragraph->text[i]);
  }
}

void JustLeft(Paragraph* paragraph) {

  for (int i = 0; i < paragraph->line_count; i++) {
    char* line_start = paragraph->text[i];
    // Remove leading spaces
    while (isspace((char)*line_start)) {
        line_start++;
    }
    
    // Move the text to the start of the line
    if (line_start != paragraph->text[i]) {
        memmove(paragraph->text[i], line_start, strlen(line_start) + 1);
    }
  }
}

void JustRight(Paragraph* paragraph) {
  Paragraph just_right;
  CreateParagraphBlock(&just_right);
  return just_right;
}

void JustBlock(Paragraph* paragraph) {
  Paragraph just_block;
  CreateParagraphBlock(&just_block);
  return just_block;
}

Paragraph PromptTextProgram() {
  printf("Welcome to TextHandler!!\n");

  Paragraph paragraph;

  printf("How long do you want your lines to be?\n");
  scanf("%u", &paragraph.line_length);

  CleanLineBuffer();

  printf("How many lines would you like to have?\n");
  scanf("%u", &paragraph.line_count);

  CleanLineBuffer();

  printf("Write some text to be justified with %d lines %d characters long.\n",
         paragraph.line_count, paragraph.line_length);
  printf("Press 'Enter' to record your text.\n\n\n");

  CreateParagraphBlock(&paragraph);

  for (unsigned int i = 0; i < paragraph.line_count; i++) {
    printf("Line %u: ", i + 1);

    // Get the data from terminal
    fgets(paragraph.text[i], paragraph.line_length + 1, stdin);
    
    // Reset text input buffer
    CleanLineBuffer();
    
    // Remove newline character if it was read
    paragraph.text[i][strcspn(paragraph.text[i], "\n")] = '\0';
  }
  return paragraph;
}