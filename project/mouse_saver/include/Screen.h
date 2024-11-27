#ifndef SCREEN_H
#define SCREEN_H

typedef struct {
  unsigned int width;
  unsigned int height;
} Screen;

/**
 * @brief Initiates screen
 *
 */
void InitScreenBuffer(void);

/**
 * @brief Frees any allocated data from screen
 *
 */
void DisposeScreenBuffer(void);

/**
 * @brief Get the Screen object
 *
 * @return Screen*
 */
Screen* GetScreen(void);

#endif  // SCREEN_H