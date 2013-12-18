// Systemy Opracyjne
// 18.12.2013 Szymon Koper
// consumer.c
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#include "additional.h"

struct shared *shared_mem;

int main(int argc, char* argv[]) {
  unsigned int sleep_time = atoi(argv[1]);
  shared_mem_init();

  int consumed_limit = 4;
  
  while(1) {
    sem_wait(&shared_mem->sem);
    //TODO
    sem_post(&shared_mem->sem);
    //TODO
    sleep(sleep_time);
  }

  return 0;
}
