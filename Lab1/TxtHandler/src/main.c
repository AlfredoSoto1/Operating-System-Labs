#include "TextHandler.h"

int main() {
  // Create a paragraph and obtain the data 
  //  from the command line
  Paragraph paragraph = PromptTextProgram();
  
  // Justify to the left the paragraph
  JustLeft(&paragraph);

  // Justify to the right the paragraph
  JustRight(&paragraph);

  FreeParagraph(&paragraph);
  return 0;
}