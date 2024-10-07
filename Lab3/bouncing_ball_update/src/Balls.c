#include "Balls.h"

#include "ProgramThreads.h"

unsigned int counter_val = 0;
unsigned int ball_count = 0;
BallProperties balls[10];

void AddBall(Screen* screen) {
  if (ball_count < MAX_BALLS) {
    BallProperties* new_ball = &balls[ball_count++];

    // Assign a random position and direction to the new ball
    new_ball->x = rand() % (screen->col - 2) + 1;
    new_ball->y = rand() % (screen->row - 2) + 1;
    new_ball->dx = rand() % 2 == 0 ? 1 : -1;
    new_ball->dy = rand() % 2 == 0 ? 1 : -1;
  }
}

void ChangeDirection() {
  for (int i = 0; i < ball_count; i++) {
    balls[i].dx *= -1;
    balls[i].dy *= -1;
  }
}