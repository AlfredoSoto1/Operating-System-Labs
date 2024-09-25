#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* Counting(void* param);
void* PrintMessage(void* param);

int main() {
  pthread_t p_counting;
  pthread_t p_print;
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  int init_counter = 6;
  char* message = "Im the second thread\0";

  pthread_create(&p_counting, &attr, Counting, (void*)&init_counter);
  pthread_create(&p_print, NULL, PrintMessage, (void*)message);

  pthread_join(p_counting, NULL);
  // pthread_join(p_print, NULL);

  return 0;
}

void* Counting(void* param) {
  int* ptr_init_c = (int*)param;

  for (int i = *ptr_init_c; i < 35; i++) {
    printf("%d\n", i);
    usleep(100000);
  }
}

void* PrintMessage(void* param) {
  char* msg = (char*)param;

  while (1) {
    printf("%s\n", msg);
    usleep(200000);
  }
}