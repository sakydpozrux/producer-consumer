// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// shared_mem.c
#include <sys/mman.h>
#include <fcntl.h>

#define PRODUCERS_NUMBER    2
#define CONSUMERS_NUMBER    4
#define PRODUCERS_SLEEP_TIME 1
#define CONSUMERS_SLEEP_TIME 2
#define PRODUCTS_LIMIT      10

void shared_mem_connect() {
  int descriptor;
  descriptor = shm_open("/prodcons", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  ftruncate(descriptor, sizeof(struct shared));

  shared_mem = mmap(NULL, sizeof(struct shared), PROT_READ | PROT_WRITE, MAP_SHARED, descriptor, 0);
}

void shared_mem_default_init() {
  shared_mem->products_consumed     = 0;
  shared_mem->products_limit        = PRODUCTS_LIMIT;
  shared_mem->producers_number      = PRODUCERS_NUMBER;
  shared_mem->consumers_number      = CONSUMERS_NUMBER;
  shared_mem->producers_sleep_time  = PRODUCERS_SLEEP_TIME;
  shared_mem->consumers_sleep_time  = CONSUMERS_SLEEP_TIME;
}

