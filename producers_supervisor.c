// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// producers_supervisor.c
//#include <stdlib.h>
//#include <sys/types.h>
//#include <sys/wait.h>
//#include <stdio.h>
//#include <errno.h>
//#include <string.h>
//#include <stdbool.h>


void create_producers() {
  printf("Creating producer process with sleep time %ds\n", producer.sleep_time);
  pid_t id = fork();
  if (id == 0) { /* child process */
      char str_sleep_time[129];
      sprintf(str_sleep_time, "%d", producer.sleep_time);
      execl("producer", "producer", str_sleep_time, NULL);
    exit(127);
  } else { /* pid != 0 <=> parent process */
    producer.id = id;
    printf("Created producer id - %d\n", id);
  }
}

void wait_for_producers() {
  waitpid(producer.id, 0, 0);
  printf("Stopped producer id - %d\n", producer.id);
}
