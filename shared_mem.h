// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// shared_mem.h
#ifndef sharedmem
#define sharedmem
//#include <unistd.h>
#include <semaphore.h>

struct shared {
  sem_t sem;
  unsigned int products_consumed;
  unsigned int products_limit;
  unsigned int producers_number;
  unsigned int consumers_number;
  unsigned int producers_sleep_time;
  unsigned int consumers_sleep_time;
} *shared_mem;


void shared_mem_connect();
void shared_mem_default_init();

#endif

