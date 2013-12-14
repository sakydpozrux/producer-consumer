#include <stdio.h>
#include <stdlib.h>

#include "additional.h"


int main(int argc, char* argv[]) {
  if (argc != 2) {
    puts("Usage example:");
    printf("%s [NUMBER OF CONSUMERS]\n", argv[0]);
    exit(1);
  } else {
    consumers.number = atoi(argv[1]);
  }

  shared_mem_init();
  shared_mem->dupa = 123;//TODO

  printf("Creating producer process\n");
  create_producer();

  printf("Creating %d consumer processes\n", consumers.number);
  create_consumers();

  wait_for_producer();
  wait_for_consumers();
  printf("DUPA-%d\n", shared_mem->dupa); //TODO
  return 0;
}
