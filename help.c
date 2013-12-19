// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// additional.h
#include <stdio.h>

void show_usage() {
  char* program_name = run.argv[0];
  printf("%s usage examples:\n", program_name);
  printf("%s [NUMBER OF CONSUMERS]\n", program_name);
  printf("%s [nr_of_CONSUMERS] [PRODUCER SLEEP TIME] [CONSUMER SLEEP TIME]\n", program_name);
}

void show_run_info() {
  printf(
    "\n"
    "Run informations: \n"
    "%d\t- number of consumers\n"
    "%d\t- waiting time for producer\n"
    "%d\t- waiting time for consumer\n"
    "\n"
    , consumers.number, producer.sleep_time, consumers.sleep_time);
}
