#include "NumberLib.h"

#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE_LIMIT 5

char* digitToWord(int digit) {
    switch(digit) {
        case 0: return "zero";
        case 1: return "one";
        case 2: return "two";
        case 3: return "three";
        case 4: return "four";
        case 5: return "five";
        case 6: return "six";
        case 7: return "seven";
        case 8: return "eight";
        case 9: return "nine";
        default: return ""; // Not a number
    }
}

int digitToWordSize(int digit) {
    switch(digit) {
        case 0: return 4;
        case 1: return 3;
        case 2: return 3;
        case 3: return 5;
        case 4: return 4;
        case 5: return 4;
        case 6: return 3;
        case 7: return 5;
        case 8: return 5;
        case 9: return 4;
        default: return 0; // Not a number
    }
}

int popDigit(int* number) {
  int pop = *number % 10;
  *number = *number / 10;
  return pop;
}

int digitCount(int number) {
  if (number == 0) return 1;
  int count = 0;
  while(number > 0) {
    number /= 10;
    count++;
  }
  return count;
}

void copy(char* str, char* dest) {
  for (int i = 0; str[i] != '\0';i++)
    dest[i] = str[i];
}

char* NumToStr(int number) {
  
  if (number < 0)
    return NULL;

  int count = digitCount(number);

  char* dest = (char*)malloc((count * MAX_WORD_SIZE_LIMIT + count + 1) * sizeof(char));

  // Create a "stack" containing the number
  int number_stack = number;
  int word = 0;

  int curNum = count - 1;
  int numBuf[count];

  // Insert zero if only number is zero
  if (number_stack == 0) {
    numBuf[curNum] = 0;
  }

  // Pop from the number stack the leftmost digit
  while(number_stack != 0) {
    numBuf[curNum--] = popDigit(&number_stack);
  }

  for (int i = 0; i < count; i ++) {
    // Convert to digit to word
    copy(digitToWord(numBuf[i]), &dest[word]);

    // Increase the word count
    word += digitToWordSize(numBuf[i]);

    if (count - i == 1)
      break;

    dest[word++] = ' ';
  }

  dest[word] = '\0';
  return dest;
}