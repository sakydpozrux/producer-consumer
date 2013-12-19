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

#define PRODUCER_SLEEP_TIME 1
#define CONSUMER_SLEEP_TIME 3

void show_usage() {
  char* program_name = run.argv[0];
  printf("%s usage examples:\n", program_name);
  printf("%s [NUMBER OF CONSUMERS]\n", program_name);
  printf("%s [nr_of_CONSUMERS] [PRODUCER SLEEP TIME] [CONSUMER SLEEP TIME]\n", program_name);
}

bool valid_arguments_counter() {
  if (run.argc == 2 || run.argc == 4) return true;
  else return false;
}

bool valid_arguments_vector() {
  if (atoi(run.argv[1]) >  0 &&
      atoi(run.argv[2]) >= 0 &&
      atoi(run.argv[3]) >= 0) return true;
  else return false;
}

bool valid_arguments() {
  if (valid_arguments_counter() && valid_arguments_vector()) return true;
  else return false;
}

void show_run_info() {
  printf(
    "Run informations: \n"
    "%d\t- number of consumers\n"
    "%d\t- waiting time for producer\n"
    "%d\t- waiting time for consumer\n"
    , consumers.number, producer.sleep_time, consumers.sleep_time);
}

void argv_init(int argc, char* argv[]) {
  run.argc = argc;
  run.argv = argv;
  
  if (valid_arguments()) {
    puts("ARGUMENTS VALID");
    consumers.number = atoi(argv[1]);

    if (argc == 4) {
      producer.sleep_time  = atoi(argv[2]);
      consumers.sleep_time = atoi(argv[3]);
    } else {
      producer.sleep_time  = PRODUCER_SLEEP_TIME;
      consumers.sleep_time = CONSUMER_SLEEP_TIME;
    }
  } else {
    show_usage();
    exit(1);
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

