#include <curses.h> /* ncurses.h incluye stdio.h */
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int counter = 0;
void* counting(void*);

pthread_mutex_t mutex;

int main() {
  pthread_t p_counter;
  pthread_t p_counter_2;

  pthread_mutex_init(&mutex, NULL);

  pthread_create(&p_counter, NULL, counting, NULL);
  pthread_create(&p_counter_2, NULL, counting, NULL);

  pthread_join(p_counter, NULL);
  pthread_join(p_counter_2, NULL);

  printf("el contador es: %d\n", counter);

  return 0;
}

void* counting(void*) {
  for (int i = 0; i < 1000000; i++) {
    pthread_mutex_lock(&mutex);
    counter++;
    pthread_mutex_unlock(&mutex);
  }
}
