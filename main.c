#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "lidx.h"
#include "option.h"
#include "locale.h"
#include "holdall.h"

static int fun_str(void *ptr, void *lid);
static int fun_file(void *ptr, void *lid);
static void *funcontext(void *context, void *ptr);

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Nombre d'arguments invalide.\n");
    exit(EXIT_FAILURE);
  }
  //--- Init var ---------------------------------------------------------------
  setlocale(LC_COLLATE, "");
  int cur_arg = 1;
  lidx *lid = lidx_empty();
  if (lid == NULL) {
    return EXIT_FAILURE;
  }
  holdall *filenames = holdall_empty();
  holdall *words = holdall_empty();
  //--- Commands ---------------------------------------------------------------
  while (argv[cur_arg] != NULL) {
    // String de base
    if (*argv[cur_arg] != '-') {
      holdall_put(words, &argv[cur_arg]);
      //lidx_add_string(lid, &argv[cur_arg]);
    }
    // Ajout fichier
    else if (strcmp(argv[cur_arg], "-") == 0) {
      ++cur_arg;
      holdall_put(filenames, (char *) argv[cur_arg]);
      //lidx_add_file(lid, (char *) argv[cur_arg]);
    } else {
      //Do nothing
    }
    ++cur_arg;
  }
  holdall_apply_context(words, fun_str, funcontext, lid);
  holdall_apply_context(filenames, fun_file, funcontext, lid);
  settings opt;
  manage_option(&opt, argc, argv);
  lidx_set_options(lid, &opt);
  lidx_add_stdin(lid, stdin);
  lidx_print(lid);
  lidx_dispose(lid);
  return EXIT_SUCCESS;
}

static int fun_str(void *ptr, void *lid) {
  return lidx_add_string(lid, ptr);
}

static int fun_file(void *ptr, void *lid) {
  return lidx_add_file(lid, (char *) ptr);
}

static void *funcontext(void *context, void *ptr) {
  if (ptr == NULL) {
    return NULL;
  }
  return context;
}
