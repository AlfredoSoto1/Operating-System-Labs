#include "ProgramThreads.h"

#include <curses.h> /* ncurses.h incluye stdio.h */
#include <string.h>
#include <unistd.h>

#include "Balls.h"

Tasks tasks;

void* ProcessRender(void* param) {
  Screen* screen = (Screen*)param;

  while (1) {
    pthread_mutex_lock(&tasks.render_lock);

    switch (screen->render) {
      case 1:
        pthread_cond_wait(&tasks.render_cond, &tasks.render_lock);
        break;
      case 2:
        pthread_mutex_unlock(&tasks.render_lock);
        endwin();

        printf("Render ended\n");
        return NULL;
    }

    clear();
    // Obtiene el numbero de filas y columnas
    getmaxyx(stdscr, screen->row, screen->col);
    mvprintw(0, 0, "Counter: %d, Balls: %d", counter_val, ball_count);

    // Render each ball
    for (int i = 0; i < ball_count; i++) {
      mvprintw(balls[i].y, balls[i].x, "o");
    }
    refresh();

    pthread_mutex_unlock(&tasks.render_lock);

    usleep(100000);
  };
}

void* ProcessPosition(void* param) {
  Screen* screen = (Screen*)param;

  while (1) {
    pthread_mutex_lock(&tasks.update_lock);

    switch (screen->update) {
      case 1:
        pthread_cond_wait(&tasks.update_cond, &tasks.update_lock);
        break;
      case 2:
        pthread_mutex_unlock(&tasks.update_lock);
        printf("Update ended\n");
        return NULL;
    }

    for (int i = 0; i < ball_count; i++) {
      balls[i].x += balls[i].dx;
      balls[i].y += balls[i].dy;
      if (balls[i].x >= screen->col - 1) {
        balls[i].dx = -1;
      }
      if (balls[i].y >= screen->row - 1) {
        balls[i].dy = -1;
      }
      if (balls[i].x <= 1) {
        balls[i].dx = 1;
      }
      if (balls[i].y <= 1) {
        balls[i].dy = 1;
      }
    }
    pthread_mutex_unlock(&tasks.update_lock);

    // Sleep for 100ms
    usleep(100000);
  }
}

void* ProcessCounter(void* param) {
  Screen* screen = (Screen*)param;

  while (1) {
    pthread_mutex_lock(&tasks.counter_lock);

    switch (screen->counter) {
      case 1:
        pthread_cond_wait(&tasks.counter_cond, &tasks.counter_lock);
        break;
      case 2:
        pthread_mutex_unlock(&tasks.counter_lock);
        printf("Counter ended\n");
        return NULL;
    }

    // Update the counter every second
    counter_val++;
    pthread_mutex_unlock(&tasks.counter_lock);

    usleep(1000000);
  }
}

void* ProcessKeyboardInput(void* param) {
  Screen* screen = (Screen*)param;

  int key_stroke;
  while (1) {
    key_stroke = getch();
    refresh();

    if (key_stroke == '\n') {
      screen->render = 0;
      screen->update = 0;
      screen->counter = 0;

      pthread_cond_signal(&tasks.render_cond);
      pthread_cond_signal(&tasks.update_cond);
      pthread_cond_signal(&tasks.counter_cond);
      break;  // Start
    }
  }

  while (1) {
    key_stroke = getch();
    refresh();
    switch (key_stroke) {
      case ' ':
        AddBall(screen);
        break;
      case 'c':
        ChangeDirection();
        break;
      case '\n':
        screen->render = 2;
        screen->update = 2;
        screen->counter = 2;
        return NULL;  // Exit
    }
  }
}

void InitializeScreen(Screen* screen) {
  // Set default values for screen
  screen->col = 10;
  screen->row = 10;
  screen->render = 1;  // True
  screen->update = 1;  // True

  // Init screen with keyboard
  initscr();
  keypad(stdscr, TRUE);
  noecho();

  curs_set(0);
}

void PrepareGame() {
  Screen screen;
  InitializeScreen(&screen);

  pthread_mutex_init(&tasks.render_lock, NULL);
  pthread_mutex_init(&tasks.update_lock, NULL);
  pthread_mutex_init(&tasks.counter_lock, NULL);

  pthread_cond_init(&tasks.render_cond, NULL);
  pthread_cond_init(&tasks.update_cond, NULL);
  pthread_cond_init(&tasks.counter_cond, NULL);

  pthread_create(&tasks.render_thread, NULL, ProcessRender, &screen);
  pthread_create(&tasks.update_thread, NULL, ProcessPosition, &screen);
  pthread_create(&tasks.counter_thread, NULL, ProcessCounter, &screen);
  pthread_create(&tasks.keyboard_input, NULL, ProcessKeyboardInput, &screen);

  pthread_join(tasks.render_thread, NULL);
  pthread_join(tasks.update_thread, NULL);
  pthread_join(tasks.counter_thread, NULL);
  pthread_join(tasks.keyboard_input, NULL);

  pthread_cond_destroy(&tasks.counter_cond);
  pthread_cond_destroy(&tasks.update_cond);
  pthread_cond_destroy(&tasks.render_cond);

  pthread_mutex_destroy(&tasks.counter_lock);
  pthread_mutex_destroy(&tasks.update_lock);
  pthread_mutex_destroy(&tasks.render_lock);
}