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
  int products_consumed;
  int products_limit;
  unsigned int producer_sleep_time;
  unsigned int consumer_sleep_time;
} *shared_mem;

#endif

