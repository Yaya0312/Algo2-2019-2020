#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include "option.h"

#define HELP_CASE 100
#define FUN_FAIL -1
#define FUN_SUCC 0
#define LOWER -1
#define AS_IS 0
#define UPPER 1
#define HELP_MESSAGE \
  "\
--help affiche l’aide selon le format usuel\n\
-S, --sort affiche la liste dans l’ordre lexicographique.\n\
-l, --case=lower converti tous les caractères lus en minuscule\n\
-s, --case=as-is laisser les caractéres tel quel\n\
-u, --case=upper converti tous les caractères lus en majuscule\n\
-i FILE, --input=FILE \
 au lieu de l’entrée standard, lire le texte dans le fichier FILE;\n\
-o FILE, --ouput=FILE \
 au lieu de la sortie standard, écrire résultat dans le fichier FILE.\n\
" \

static struct option long_options[] = {
  {"help", no_argument, NULL, HELP_CASE },
  {"sort", no_argument, NULL, 'S' },
  {"case", required_argument, NULL, 0 },
  {"input", required_argument, NULL, 'i' },
  {"output", required_argument, NULL, 'o'},
  {0, 0, 0, 0 }
};

int manage_option(settings *opt, int argc, const char *argv[]) {
  //init struct
  opt->sort = false;
  opt->case_word = AS_IS;
  opt->stream_in = stdin;
  opt->stream_out = stdout;
  int c;
  while (1) {
    int option_index = 0;
    c = getopt_long(argc, (char * const *) argv, "lsui:o:S",
            long_options, &option_index);
    if (c == -1) {
      return FUN_SUCC;
    }
    switch (c) {
      case HELP_CASE:
        printf(HELP_MESSAGE);
        exit(EXIT_SUCCESS);
      case 'S':
        opt->sort = true;
        break;
      case 'c':
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
        opt->stream_in = fopen(optarg, "r");
        if (opt->stream_in == NULL) {
          return FUN_FAIL;
        }
        break;
      case 'o':
        opt->stream_out = fopen(optarg, "w");
        if (opt->stream_out == NULL) {
          return FUN_FAIL;
        }
        break;
    }
  }
  return FUN_SUCC;
}

void option_debug(settings *opt) {
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