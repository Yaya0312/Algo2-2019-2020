#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include "option.h"

#define HELP 100
#define CASE 101
#define FUN_FAIL -1
#define FUN_SUCC 0
#define HELP_MESSAGE \
  "\
--help affiche l’aide selon le format usuel\n\
-S, --sort affiche la liste dans l’ordre lexicographique.\n\
-l, --case=lower converti tous les caractères lus en minuscule\n\
-s, --case=as-is laisser les caractéres tel quel\n\
-u, --case=upper converti tous les caractères lus en majuscule\n\
-i FILE, --input=FILE \
 au lieu de l’entrée standard, lire le texte dans le fichier FILE\n\
" \

static struct option long_options[] = {
  {"help", no_argument, NULL, HELP },
  {"sort", no_argument, NULL, 'S' },
  {"case", required_argument, NULL, CASE},
  {"input", required_argument, NULL, 'i' },
  {"output", required_argument, NULL, 'o'},
  {0, 0, 0, 0 }
};

void manage_option(options *opt, int argc, const char *argv[]) {
  //init struct
  opt->sort = false;
  opt->case_word = AS_IS;
  opt->stream_in = NULL;
  opt->stream_out = NULL;
  int c;
  while (1) {
    int option_index = 0;
    c = getopt_long(argc, (char * const *) argv, "lsui:o:S",
            long_options, &option_index);
    if (c == -1) {
      return;
    }
    switch (c) {
      case HELP:
        printf(HELP_MESSAGE);
        exit(EXIT_SUCCESS);
      case 'S':
        opt->sort = true;
        break;
      case CASE:
        if (strcmp(optarg, "lower") == 0) {
          opt->case_word = LOWER;
        } else if (strcmp(optarg, "as-is") == 0) {
          opt->case_word = AS_IS;
        } else if (strcmp(optarg, "upper") == 0) {
          opt->case_word = UPPER;
        }
        break;
      case 'l':
        opt->case_word = LOWER;
        break;
      case 's':
        opt->case_word = AS_IS;
        break;
      case 'u':
        opt->case_word = UPPER;
        break;
      case 'i':
        opt->stream_in = optarg;
        break;
      case 'o':
        opt->stream_out = optarg;
        break;
    }
  }
}

void option_debug(options *opt) {
  printf("Trie par ordre alphabetique: ");
  opt->sort ? printf("Oui\n") : printf("Non\n");
  printf("Changement de la casse:");
  if (opt->case_word == LOWER) {
    printf("minuscule\n");
  }
  if (opt->case_word == AS_IS) {
    printf("non\n");
  }
  if (opt->case_word == UPPER) {
    printf("majuscule\n");
  }
}
