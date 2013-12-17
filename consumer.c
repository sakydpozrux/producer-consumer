#include <stdio.h>
#include <stdlib.h>

#include "additional.h"

struct shared *shared_mem;

int main(int argc, char* argv[]) {
  unsigned int sleep_time = atoi(argv[1]);
  shared_mem_init();
  sleep(3);
  
  while(0) {
    //TODO
    sleep(sleep_time);
  }
  printf("CONSUMER\n");
  return 0;
}
