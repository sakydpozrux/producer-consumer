// Systemy Opracyjne
// 18.12.2013 Szymon Koper
// additional.c
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "additional.h"


void argv_init(int argc, char* argv[]) {
  if (argc < 2 || argc > 4) {
    puts("Usage example:");
    printf("%s [NUMBER OF CONSUMERS]\n", argv[0]);
    exit(1);
  } else {
    consumers.number = atoi(argv[1]);
  }

  if (argc == 4) {
    producer.sleep_time  = atoi(argv[2]);
    consumers.sleep_time = atoi(argv[3]);
  } else {
    producer.sleep_time  = 1;
    consumers.sleep_time = 3;
  }
}

void shared_mem_init() {
  int descriptor;
  descriptor = shm_open("/prodcons", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  ftruncate(descriptor, sizeof(struct shared));

  shared_mem = mmap(NULL, sizeof(struct shared), PROT_READ | PROT_WRITE, MAP_SHARED, descriptor, 0);

  shared_mem->fruits_number = 0;
}

void create_producer() {
  printf("Creating producer process with sleep time %ds\n", producer.sleep_time);
  pid_t id = fork();
  if (id == 0) { /* child process */
      char str_sleep_time[129];
      sprintf(str_sleep_time, "%d", producer.sleep_time);
      execl("producer", "producer", str_sleep_time, NULL);
    exit(127);
  } else { /* pid != 0 <=> parent process */
    producer.id = id;
    printf("Created producer id - %d\n", id);
  }
}

void create_consumers() {
  printf("Creating %d consumer processes with sleep time %ds\n", consumers.number, consumers.sleep_time);
  consumers.list = malloc(consumers.number * sizeof(pid_t));
  pid_t* p = consumers.list;
  for (int i = 0; i < consumers.number; ++i, ++p) {
    pid_t id = fork();
    if (id == 0) { /* child process */
      char str_sleep_time[129];
      sprintf(str_sleep_time, "%d", consumers.sleep_time);
      execl("consumer", "consumer", str_sleep_time, NULL);
      exit(127);
    } else { /* pid != 0 <=> parent process */
      *p = id;
      printf("Created consumer id - %d\n", id);
    }
  }
}

void wait_for_producer() {
  waitpid(producer.id, 0, 0);
  printf("Stopped producer id - %d\n", producer.id);
}

void wait_for_consumers() {
  pid_t* current_consumer = consumers.list;
  for (int i = 0; i < consumers.number; ++i, ++current_consumer) {
    waitpid(*current_consumer, 0, 0);
    printf("Stopped consumer id - %d\n", *current_consumer);
  }
}

