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
void wait_for_consumers();

struct shared {
  sem_t i_sem;
} *shared_mem;

struct consumers {
  int number;
  pid_t* list;
} consumers;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    puts("Usage example:");
    printf("%s [NUMBER OF CONSUMERS]\n", argv[0]);
    exit(1);
  }

  shared_mem_init();

  printf("Creating producer process\n");
  create_producer();

  const int consumers.number = atoi(argv[1]);
  printf("Creating %d consumers.\n", consumers.number);
  create_consumers();

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
    execl("/bin/echo", "echo", "Foo is my name.", NULL);
    exit(127);
  } else { /* pid != 0 <=> parent process */
    waitpid(id, 0, 0); /* wait for child to exit */
  }
}

void create_consumers() {
  for (int i = 0; i < consumer.number; ++i) {
    pid_t id = fork();
    if (id == 0) { /* child process */
      execl("/bin/echo", "echo", "Foo is my name.", NULL);
      exit(127);
    } else { /* pid != 0 <=> parent process */
      waitpid(id, 0, 0); /* wait for child to exit */
    }
  }
}

void wait_for_consumers() {
  pid_t* current_consumer = consumer.list;

  for (int i = 0; i < consumer.number; ++i, ++current_consumer)
    waitpid(*current_consumer, 0, 0);
}
