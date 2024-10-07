#ifndef BALLS_H
#define BALLS_H

#define MAX_BALLS 10

typedef struct Screen Screen;

/**
 * @brief Holds the properties of a single ball
 *
 */
typedef struct BallProperties {
  int x;
  int y;
  int dx;
  int dy;
} BallProperties;

extern unsigned int ball_count;
extern BallProperties balls[10];

/**
 * @brief Adds a ball to the screen to render [0, 10)
 *
 * @param screen
 */
void AddBall(Screen* screen);

/**
 * @brief Changes the direction of the balls
 *
 */
void ChangeDirection();

#endif  // BALLS_H