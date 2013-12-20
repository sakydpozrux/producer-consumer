// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// consumer.c
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>

#include "shared_mem.h"

struct shared *shared_mem;

int main() {
  shared_mem_connect();

  const unsigned int pid = getpid();

  const unsigned int products_limit = shared_mem->products_limit;
  const unsigned int sleep_time = shared_mem->consumers.sleep_time;

  unsigned int products_consumed = 0;
  
  while(1) {
    sem_wait(&shared_mem->sem);
    if (shared_mem->products_consumed >= products_limit) {
      printf("Consumer %u exiting with %u consumed.\n",
          pid, products_consumed);
      sem_post(&shared_mem->sem);
      break;
    } else {
      if (shared_mem->products_ready > 0) {
        ++shared_mem->products_consumed;
        --shared_mem->products_ready;
        printf("Consumed 1 product by %u. Total products - %u\n",
            pid, shared_mem->products_ready);
        ++products_consumed;
      }
      sem_post(&shared_mem->sem);
    }

    sleep(sleep_time);
  }

  return 0;
}
