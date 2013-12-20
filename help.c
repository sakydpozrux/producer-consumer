// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// help.c
#include <stdio.h>
#include <sys/types.h>

#include "help.h"
#include "producers_supervisor.h"
#include "consumers_supervisor.h"
#include "shared_mem.h"


void show_usage() {
  char* program_name = "program";
  printf("usage: %s [OPTION [<value>]]...\n", program_name);
  printf("\n");
  printf("List of arguments:\n");
  printf("\t-p | --producents-number <value>   Set number of producent processes\n");
  printf("\t-c | --consumers-number <value>    Set number of consumer processes\n");
  printf("\t-m | --producents-wait <value>     Set waiting time for producer process after producing\n");
  printf("\t-e | --consumers-wait <value>      Set waiting time for consumer process after consuming\n");
  printf("\t-l | --limit <value>               Set limit of total products to produce\n");
  printf("\t-h | --help                        Display this help\n");
}

void show_run_info() {
  printf(
    "\n"
    "Run informations: \n"
    "%d\t- number of consumers\n"
    "%d\t- waiting time for producer\n"
    "%d\t- waiting time for consumer\n"
    "\n"
    , shared_mem->consumers.number, shared_mem->producers.sleep_time, shared_mem->consumers.sleep_time);
}
