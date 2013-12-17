#include <stdio.h>
#include <stdlib.h>

#include "additional.h"

struct shared *shared_mem;

int main(int argc, char* argv[]) {
  unsigned int sleep_time = atoi(argv[1]);
  shared_mem_init();
  sleep(4);

  while(0) {
    //TODO
    sleep(sleep_time);
  }
  //shared_mem->dupa = 997;//TODO
  printf("\n");
  return 0;
}
