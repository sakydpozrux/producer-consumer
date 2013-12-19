// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// consumers_supervisor.h
#ifndef consumerssupervisor
#define consumerssupervisor
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
} consumers;


void create_consumers();
void wait_for_consumers();

#endif

