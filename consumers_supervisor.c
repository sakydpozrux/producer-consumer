// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// consumers_supervisor.c
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "consumers_supervisor.h"
#include "shared_mem.h"

void create_consumers() {
  printf("Creating %d consumer processes with sleep time %ds\n", shared_mem->consumers.number, shared_mem->consumers.sleep_time);
  shared_mem->consumers.list = malloc(shared_mem->consumers.number * sizeof(pid_t));
  pid_t* p = shared_mem->consumers.list;
  for (int i = 0; i < shared_mem->consumers.number; ++i, ++p) {
    pid_t id = fork();
    if (id == 0) { /* child process */
      char str_sleep_time[129];
      sprintf(str_sleep_time, "%d", shared_mem->consumers.sleep_time);
      execl("consumer", "consumer", str_sleep_time, NULL);
      exit(EXIT_FAILURE);
    } else { /* pid != 0 <=> parent process */
      *p = id;
      printf("Created consumer id - %d\n", id);
    }
  }
}

void wait_for_consumers() {
  pid_t* current_consumer = shared_mem->consumers.list;
  for (int i = 0; i < shared_mem->consumers.number; ++i, ++current_consumer) {
    waitpid(*current_consumer, 0, 0);
    printf("Stopped consumer id - %d\n", *current_consumer);
  }
}

