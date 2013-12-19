#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>

struct option long_options[] = {
  {"producents-number", required_argument, 0, 'p'},
  {"consumers-number",  required_argument, 0, 'c'},
  {"producents-wait",   required_argument, 0, 'm'},
  {"consumers-wait",    required_argument, 0, 'e'},
  {"limit",             required_argument, 0, 'l'},
  {0,                   0,                 0,  0 }
};

int print_setting(char* name, char* value) {
  return printf("Setting '%s' with value '%s'\n", name, value);
}

int main(int argc, char **argv)
{
  int c;
  int option_index = 0;

  while ((c = getopt_long(argc, argv, "p:c:m:e:l:", long_options, &option_index)) != -1) {
    switch (c) {
      case 'p':
        print_setting("producents number", optarg);
        break;

      case 'c':
        print_setting("consumers number", optarg);
        break;

      case 'm':
        print_setting("producents waiting time", optarg);
        break;

      case 'e':
        print_setting("consumers waiting time", optarg);
        break;

      case 'l':
        print_setting("total products limit", optarg);
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

  exit(EXIT_SUCCESS);
}

