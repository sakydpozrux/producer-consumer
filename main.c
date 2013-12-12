#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

#define PROCESSES 1

struct shared {
  sem_t p_sem;
  sem_t c_sem;
  int products_counter;
} *shared_mem;

void producer(void) {
  while(TRUE) {
    // producing code here
    printf("Produced\n");
  }
}

void consumer(void) {
  while(TRUE) {
    // consuming code here
    printf("Consumed\n");
  }
}

void run_tests(void);

int main(int argc, char* argv[]) {
  run_tests();

  shared_mem = mmap(NULL, sizeof(struct shared), PROT_READ | PROT_WRITE,
      MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  sem_init(&shared_mem->p_sem, 1, 1);
  sem_init(&shared_mem->c_sem, 1, 0);
  shared_mem->products_counter = 0;

  const int cnt_consuments = atoi(argv[1]);


  return 0;
}

void run_tests(void) {
  assert(TRUE  == 1);
  assert(FALSE == 0);
  assert(PROCESSES > 0);
}
