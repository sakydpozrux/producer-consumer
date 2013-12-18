// Systemy Opracyjne
// 18.12.2013 Szymon Koper
// additional.h
#ifndef helpful
#define helpful
#include <unistd.h>
#include <semaphore.h>


void argv_init();
void shared_mem_init();
void create_producer();
void create_consumers();
void wait_for_producer();
void wait_for_consumers();

struct shared {
  sem_t sem;
  int fruits_number;
} *shared_mem;

struct {
  pid_t id;
  unsigned int sleep_time;
} producer;

struct {
  int number;
  pid_t* list;
  unsigned int sleep_time;
} consumers;

#endif

