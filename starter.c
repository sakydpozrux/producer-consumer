// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// starter.c
#include "argsinit.h"
#include "help.h"
#include "shared_mem.h"
#include "producers_supervisor.h"
#include "consumers_supervisor.h"

int main(int argc, char* argv[]) {
  shared_mem_connect();

  shared_mem_default_init();
  args_init(argc, argv);

  show_run_info();

  create_producers();
  create_consumers();

  wait_for_producers();
  wait_for_consumers();

  return 0;
}
