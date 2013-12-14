#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>

#include "additional.h"


void shared_mem_init() {
  int descriptor;
  descriptor = shm_open("/prodcons", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  ftruncate(descriptor, sizeof(struct shared));

  shared_mem = mmap(NULL, sizeof(struct shared), PROT_READ | PROT_WRITE, MAP_SHARED, descriptor, 0);
}

void create_producer() {
  pid_t id = fork();
  if (id == 0) { /* child process */
    execl("producer", "producer", NULL);
    exit(127);
  } else { /* pid != 0 <=> parent process */
    producer.id = id;
    printf("Created producer id - %d\n", id);
  }
}

void create_consumers() {
  consumers.list = malloc(consumers.number * sizeof(pid_t));
  pid_t* p = consumers.list;
  for (int i = 0; i < consumers.number; ++i, ++p) {
    pid_t id = fork();
    if (id == 0) { /* child process */
      execl("consumer", "consumer", NULL);
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

