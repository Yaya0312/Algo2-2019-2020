#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "lidx.h"
#include "option.h"
#include "locale.h"

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Nombre d'arguments invalide.\n");
    exit(EXIT_FAILURE);
  }
  // ****************** Init Var *********************************************//
  setlocale(LC_COLLATE, "");
  int cur_arg = 1;
  lidx *lid = lidx_empty();
  if (lid == NULL) {
    return EXIT_FAILURE;
  }
  // ****************** Gestion arguments ************************************//
  while (argv[cur_arg] != NULL) {
    // String de base
    if (*argv[cur_arg] != '-') {
      lidx_add_string(lid, &argv[cur_arg]);
    }
    // Ajout fichier
    else if (strcmp(argv[cur_arg], "-") == 0) {
      ++cur_arg;
      lidx_add_file(lid, (char *) argv[cur_arg]);
    } else {
      //Do nothing
    }
    ++cur_arg;
  }
  settings opt;
  manage_option(&opt, argc, argv);
  lidx_set_options(lid, &opt);
  lidx_add_stdin(lid, stdin);
  lidx_print(lid);
  lidx_dispose(lid);
  return EXIT_SUCCESS;
}
