#include "TextHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void CreateParagraphBlock(Paragraph* paragraph) {
  paragraph->text = (char**)malloc(paragraph->line_count * sizeof(char*));

  for (int i = 0; i < paragraph->line_count; i++)
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
  printf("\n");
}

void JustLeft(Paragraph* paragraph) {
  for (int i = 0; i < paragraph->line_count; i++) {
    char* line_start = paragraph->text[i];

    // Remove leading spaces
    while (isspace((char)*line_start)) {
      line_start++;
    }

    // Calculate the length of the sentence after removing leading spaces
    size_t sentence_length = strlen(line_start);

    // Move the text to the start of the line
    memmove(paragraph->text[i], line_start, sentence_length);

    // Set to free space the left out memory when shifting to the left
    for (unsigned int j = sentence_length; j < paragraph->line_length; j++) {
      paragraph->text[i][j] = ' ';
    }

    paragraph->text[i][paragraph->line_length] = '\0';
  }
}

void JustRight(Paragraph* paragraph) {
  for (int i = 0; i < paragraph->line_count; i++) {
    char* line_end = paragraph->text[i] + paragraph->line_length - 1;

    // Remove not leading spaces
    while (isspace((char)*line_end)) {
      line_end--;
    }

    size_t sentence_length = line_end - paragraph->text[i] + 1;
    size_t start_pos = paragraph->line_length - sentence_length;

    memmove(paragraph->text[i] + start_pos, paragraph->text[i],
            sentence_length);

    //  Place empty spaces on places where dirty memory is left
    for (unsigned int j = 0; j < start_pos; j++) {
      paragraph->text[i][j] = ' ';
    }

    paragraph->text[i][paragraph->line_length] = '\0';
  }
}

void JustBlock(Paragraph* paragraph) {
  for (int i = 0; i < paragraph->line_count; ++i) {
    char* sentence = paragraph->text[i];

    // Skip the spaces from left if any
    char* start_line = sentence;
    while (*start_line == ' ') {
      start_line++;
    }

    // Skip spaces from the right if any
    char* end = sentence + strlen(sentence) - 1;
    while (end > start_line && *end == ' ') {
      end--;
    }
    // Add the null termination when shrinking the string
    *(end + 1) = '\0';

    // Split line into words
    // Only 100 words as a current limit
    char* words[100];
    unsigned int word_count = 0;

    // Separate the sentence into words
    char* token = strtok(start_line, " ");
    while (token != NULL) {
      words[word_count++] = token;
      token = strtok(NULL, " ");
    }

    // If there's only one word, no need to justify
    if (word_count == 1) {
      strncpy(paragraph->text[i], words[0], paragraph->line_length);
      paragraph->text[i][paragraph->line_length] = '\0';
      continue;
    }

    // Calculate space distribution
    int total_spaces = paragraph->line_length - (end - start_line + 1);
    int space_per_gap = total_spaces / (word_count - 1);
    int extra_spaces = total_spaces % (word_count - 1);

    // Create a temporary buffer to hold the new
    // justified text. This will get deleted later
    char* new_line = (char*)malloc((paragraph->line_length + 1) * sizeof(char));
    new_line[0] = '\0';

    for (int j = 0; j < word_count; j++) {
      strcat(new_line, words[j]);
      if (j < word_count - 1) {
        for (int k = 0; k < space_per_gap + 1; k++) {
          strcat(new_line, " ");
        }
        if (extra_spaces > 0) {
          strcat(new_line, " ");
          --extra_spaces;
        }
      }
    }

    // Copy the justified paragraph to the given paragraph
    // pointer again and delete the other buffer reference
    strncpy(paragraph->text[i], new_line, paragraph->line_length);
    paragraph->text[i][paragraph->line_length] = '\0';
    free(new_line);
  }
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

    // Check if the input exceeded the line length
    if (strchr(paragraph.text[i], '\n') == NULL) {
      // Clean the remaining input buffer if no newline was found
      CleanLineBuffer();
    }

    // Remove newline character if it was read
    size_t length = strlen(paragraph.text[i]);
    if (length > 0 && paragraph.text[i][length - 1] == '\n') {
      paragraph.text[i][length - 1] = '\0';
      length--;
    }

    // Fill the rest of the line with spaces if input is shorter than
    // line_length
    if (length < paragraph.line_length) {
      memset(paragraph.text[i] + length, ' ', paragraph.line_length - length);
      paragraph.text[i][paragraph.line_length] = '\0';
    }
  }

  // Ask the user for the type of justification
  unsigned int justification;

  do {
    printf(
        "\n1. Left Justify   2. Right Justify  3. Block Justify  4. "
        "None(Exit)\n\n");
    scanf("%u", &justification);

    switch (justification) {
      case 1:
        JustLeft(&paragraph);
        break;
      case 2:
        JustRight(&paragraph);
        break;
      case 3:
        JustBlock(&paragraph);
        break;
      default:
        // No justification
        return paragraph;
    }

    PrintParagraph(&paragraph);
  } while (1);

  return paragraph;
}