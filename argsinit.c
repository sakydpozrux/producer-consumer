// 19.12.2013
// Systemy Operacyjne 
// prowadzacy - Zdzislaw Ploski
// autor      - Szymon Koper
// argsinit.c
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "help.h"
#include "shared_mem.h"

struct option long_options[] = {
  {"producents-number", required_argument, 0, 'p'},
  {"consumers-number",  required_argument, 0, 'c'},
  {"producents-wait",   required_argument, 0, 'm'},
  {"consumers-wait",    required_argument, 0, 'e'},
  {"limit",             required_argument, 0, 'l'},
  {"help",              no_argument,       0, 'h'},
  {0,                   0,                 0,  0 }
};

int print_setting(char* name, char* value) {
  return printf("Setting '%s' with value '%s'\n", name, value);
}

void args_init(int argc, char** argv)
{
  int c;
  int option_index = 0;

  while ((c = getopt_long(argc, argv, "p:c:m:e:l:h", long_options, &option_index)) != -1) {
    switch (c) {
      case 'p':
        print_setting("producents number", optarg);
        if (atoi(optarg) >= 0)
          shared_mem->producers.number = atoi(optarg);
        break;

      case 'c':
        print_setting("consumers number", optarg);
        if (atoi(optarg) >= 0)
          shared_mem->consumers.number = atoi(optarg);
        break;

      case 'm':
        print_setting("producents waiting time", optarg);
        if (atoi(optarg) >= 0)
          shared_mem->producers.sleep_time = atoi(optarg);
        break;

      case 'e':
        print_setting("consumers waiting time", optarg);
        if (atoi(optarg) >= 0)
          shared_mem->consumers.sleep_time = atoi(optarg);
        break;

      case 'l':
        print_setting("total products limit", optarg);
        if (atoi(optarg) >= 0)
          shared_mem->products_limit = atoi(optarg);
        break;

      case 'h':
        show_usage();
        exit(EXIT_SUCCESS);
        break;

      case '?':
        break;

      default:
        printf("?? getopt returned character code 0%o ??\n", c);
    }
  }

  if (optind < argc) {
    printf("non-option ARGV-elements: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);
    printf("\n");
  }
}

