// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// producers_supervisor.c
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "producers_supervisor.h"
#include "shared_mem.h"


void create_producers() {
  printf("Creating %d producer processes with sleep time %ds\n", shared_mem->producers.number, shared_mem->producers.sleep_time);
  shared_mem->producers.list = malloc(shared_mem->producers.number * sizeof(pid_t));
  pid_t* p = shared_mem->producers.list;
  for (int i = 0; i < shared_mem->producers.number; ++i, ++p) {
    pid_t id = fork();
    if (id == 0) { /* child process */
      char str_sleep_time[129];
      sprintf(str_sleep_time, "%d", shared_mem->producers.sleep_time);
      execl("producer", "producer", str_sleep_time, NULL);
      exit(EXIT_FAILURE);
    } else { /* pid != 0 <=> parent process */
      *p = id;
      printf("Created producer id - %d\n", id);
    }
  }
}

void wait_for_producers() {
  pid_t* current_producer = shared_mem->producers.list;
  for (int i = 0; i < shared_mem->producers.number; ++i, ++current_producer) {
    waitpid(*current_producer, 0, 0);
    printf("Stopped producer id - %d\n", *current_producer);
  }
}

