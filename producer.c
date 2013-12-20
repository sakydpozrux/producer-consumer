// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// producer.c
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>

#include "shared_mem.h"


int main() {
  shared_mem_connect();

  const unsigned int pid = getpid();

  const unsigned int products_limit = shared_mem->products_limit;
  const unsigned int sleep_time = shared_mem->producers.sleep_time;

  unsigned int products_produced = 0;

  while(1) {
    sem_wait(&shared_mem->sem);
    if (shared_mem->products_produced >= products_limit) {
      printf("Producer %u exiting with %u made.\n",
          pid, products_produced);
      sem_post(&shared_mem->sem);
      break;
    } else {
      ++shared_mem->products_produced;
      ++shared_mem->products_ready;
      printf("Produced 1 product by %u. Total products - %u\n",
          pid, shared_mem->products_ready);
      sem_post(&shared_mem->sem);
      ++products_produced;
    }

    sleep(sleep_time);
  }

  return 0;
}
