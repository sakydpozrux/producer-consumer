// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// producers_supervisor.h
#ifndef producerssupervisor
#define producerssupervisor
//#include <stdlib.h>
//#include <sys/types.h>
//#include <sys/wait.h>
//#include <stdio.h>
//#include <errno.h>
//#include <string.h>


struct {
  int number;
  pid_t* list;
  unsigned int sleep_time;
  //unsigned int products_limit;
} producers;


void create_producers();
void wait_for_producers();

#endif

