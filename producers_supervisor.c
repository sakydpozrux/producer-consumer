// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// producers_supervisor.c
//#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include <errno.h>
//#include <string.h>
//#include <stdbool.h>

#include "producers_supervisor.h"


void create_producers() {
  printf("Creating %d producer processes with sleep time %ds\n", producers.number, producers.sleep_time);
  producers.list = malloc(producers.number * sizeof(pid_t));
  pid_t* p = producers.list;
  for (int i = 0; i < producers.number; ++i, ++p) {
    pid_t id = fork();
    if (id == 0) { /* child process */
      char str_sleep_time[129];
      sprintf(str_sleep_time, "%d", producers.sleep_time);
      execl("producer", "producer", str_sleep_time, NULL);
      exit(EXIT_FAILURE);
    } else { /* pid != 0 <=> parent process */
      *p = id;
      printf("Created producer id - %d\n", id);
    }
  }
}

void wait_for_producers() {
  pid_t* current_producer = producers.list;
  for (int i = 0; i < producers.number; ++i, ++current_producer) {
    waitpid(*current_producer, 0, 0);
    printf("Stopped producer id - %d\n", *current_producer);
  }
}

