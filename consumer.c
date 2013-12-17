#include <stdio.h>

#include "additional.h"

struct shared *shared_mem;

int main(int argc, char* argv[]) {
  shared_mem_init();
  shared_mem->dupa = 997;//TODO
  return 0;
}
