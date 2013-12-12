#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>


void shared_mem_init();
void create_producer();
void create_consumers();
void wait_for_producer();
void wait_for_consumers();

struct shared {
  sem_t i_sem;
} *shared_mem;

struct {
  pid_t id;
} producer;

struct {
  int number;
  pid_t* list;
} consumers;

pid_t producer_id;


int main(int argc, char* argv[]) {
  if (argc != 2) {
    puts("Usage example:");
    printf("%s [NUMBER OF CONSUMERS]\n", argv[0]);
    exit(1);
  } else {
    consumers.number = atoi(argv[1]);
  }

  shared_mem_init();

  printf("Creating producer process\n");
  create_producer();

  printf("Creating %d consumers.\n", consumers.number);
  create_consumers();

  wait_for_producer();
  wait_for_consumers();

  return 0;
}

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
    }
  }
}

void wait_for_producer() {
  waitpid(producer.id, 0, 0);
}

void wait_for_consumers() {
  pid_t* current_consumer = consumers.list;
  for (int i = 0; i < consumers.number; ++i, ++current_consumer)
    waitpid(*current_consumer, 0, 0);
}

