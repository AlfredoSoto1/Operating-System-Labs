#include <curses.h> /* ncurses.h incluye stdio.h */
#include <pthread.h>
#include <string.h>
#include <unistd.h>

typedef struct BallProperties {
  int x;
  int y;
  int dx;
  int dy;
} BallProperties;

typedef struct Screen {
  int row;
  int col;
} Screen;

#define ENTER_NCURSES 10

void* ProcessPosition(void* process_position_params) {
  Screen* screen = (Screen*)&process_position_params[0];
  BallProperties* properties = (BallProperties*)&process_position_params[1];

  properties->dx = 1;
  properties->dy = 1;

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

int main() {
  Screen screen;

  BallProperties properties;
  properties.x = 10;
  properties.y = 20;

  void* process_position_params[2];

  process_position_params[0] = &screen;
  process_position_params[1] = &properties;

  pthread_t id1, id2;

  pthread_create(&id1, NULL, ProcessPosition, process_position_params);
  pthread_join(id1, NULL);

  initscr();
  keypad(stdscr, TRUE);
  noecho();

  curs_set(0);

  int counter_val = 0;

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

  while (1) {
    clear();
    // Obtiene el numbero de filas y columnas
    getmaxyx(stdscr, screen.row, screen.col);
    mvprintw(0, 0, "%d", counter_val++);
    mvprintw(properties.y, properties.x, "o");
    refresh();
  }

  getch();
  endwin();

  return 0;
}