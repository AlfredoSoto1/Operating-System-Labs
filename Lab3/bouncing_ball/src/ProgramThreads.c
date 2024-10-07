#include "ProgramThreads.h"

#include <curses.h> /* ncurses.h incluye stdio.h */
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void* ProcessPosition(void* param) {
  void** param_new = param;
  Screen* screen = (Screen*)param_new[0];
  BallProperties* properties = (BallProperties*)param_new[1];

  while (1) {
    properties->x += properties->dx;
    properties->y += properties->dy;
    if (properties->x >= screen->col - 1) {
      properties->dx = -1;
    }
    if (properties->y >= screen->row - 1) {
      properties->dy = -1;
    }
    if (properties->x <= 1) {
      properties->dx = 1;
    }
    if (properties->y <= 1) {
      properties->dy = 1;
    }

    // Sleep for 100ms
    usleep(100000);
  }
}

void* ProcessCounter(void* param) {
  int* counter_val = (int*)param;

  while (1) {
    (*counter_val)++;

    // Sleep for one second
    usleep(1000000);
  }
}

void WaitForUser() {
  int key_stroke;
  int break_loop = 0;
  while (!break_loop) {
    key_stroke = getch();
    refresh();
    switch (key_stroke) {
      case KEY_LEFT:
        /* code */
        break;
      case 'f':
        /* code */
        break;
      case ENTER_NCURSES:
        // case KEY_ENTER:
        break_loop = 1;
        break;
    }
  }
}

void PrepareRender() {
  Screen screen;
  BallProperties properties;
  properties.x = 10;
  properties.y = 20;

  properties.dx = 1;
  properties.dy = 1;

  void* params[2];
  params[0] = &screen;
  params[1] = &properties;

  // Prepare counter
  int counter_val = 0;

  // Initiate screen
  initscr();
  keypad(stdscr, TRUE);
  noecho();

  curs_set(0);

  // Wait for user to press 'Enter' to start rendering
  WaitForUser();

  pthread_t id1, id2;
  pthread_create(&id1, NULL, ProcessPosition, params);
  pthread_create(&id2, NULL, ProcessCounter, &counter_val);

  // Render loop
  while (1) {
    clear();
    // Obtiene el numbero de filas y columnas
    getmaxyx(stdscr, screen.row, screen.col);
    mvprintw(0, 0, "Counter: %d", counter_val);
    mvprintw(properties.y, properties.x, "o");
    refresh();

    // Sleep for 100ms
    usleep(100000);
  }

  getch();
  endwin();

  pthread_join(id1, NULL);
  pthread_join(id2, NULL);
}