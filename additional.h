#ifndef helpful
#define helpful
#include <unistd.h>
#include <semaphore.h>


void shared_mem_init();
void create_producer();
void create_consumers();
void wait_for_producer();
void wait_for_consumers();

struct shared {
  sem_t i_sem;
  int dupa;//TODO
} *shared_mem;

struct {
  pid_t id;
} producer;

struct {
  int number;
  pid_t* list;
} consumers;

#endif

