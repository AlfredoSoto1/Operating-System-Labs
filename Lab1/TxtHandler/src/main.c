#include "TextHandler.h"

int main() {
  // Create a paragraph and obtain the data
  //  from the command line
  Paragraph paragraph = PromptTextProgram();

  // Use the paragraph text for anything

  // Free the allocated paragraph
  FreeParagraph(&paragraph);
  return 0;
}