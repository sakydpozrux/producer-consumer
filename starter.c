#include <stdio.h>

#include "additional.h"


int main(int argc, char* argv[]) {
  argv_init(argc, argv);
  shared_mem_init();

  printf("Creating producer process with sleep time %ds\n", producer.sleep_time);
  create_producer();

  printf("Creating %d consumer processes with sleep time %ds\n", consumers.number, consumers.sleep_time);
  create_consumers();

  wait_for_producer();
  wait_for_consumers();

  return 0;
}
