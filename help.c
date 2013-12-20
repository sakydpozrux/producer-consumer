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
  printf("\n");
  printf("Default values:\n");
  printf("\t--producents-number\t2\n");
  printf("\t--consumers-number \t4\n");
  printf("\t--producents-wait  \t1\n");
  printf("\t--consumers-wait   \t2\n"); 
  printf("\t--limit            \t10\n");

  printf("\n");
  printf("Author:   Szymon Koper -- sakydpozrux\n");
  printf("Date:     18.12.2013\n");
}

void show_run_info() {
  printf("\n");
  printf("Run informations: \n");
  printf("%u\t- number of producers\n",       shared_mem->producers.number);
  printf("%u\t- number of consumers\n",       shared_mem->consumers.number);
  printf("%u\t- waiting time for producer\n", shared_mem->producers.sleep_time);
  printf("%u\t- waiting time for consumer\n", shared_mem->consumers.sleep_time);
  printf("%u\t- limit of total products\n",   shared_mem->products_limit);
  printf("Run -h or --help for more informations.\n");
  printf("\n");
}
