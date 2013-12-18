// Systemy Opracyjne
// 18.12.2013 Szymon Koper
// starter.c
#include "additional.h"

int main(int argc, char* argv[]) {
  argv_init(argc, argv);
  shared_mem_init();

  create_producer();
  create_consumers();

  wait_for_producer();
  wait_for_consumers();

  return 0;
}
