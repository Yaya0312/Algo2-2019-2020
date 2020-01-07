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
  int command_arg = 0;
  char *arg_commands[argc];
  lidx *lid = lidx_empty();
  if (lid == NULL) {
    return EXIT_FAILURE;
  }
  holdall *filenames = holdall_empty();
  if (filenames == NULL) {
    return EXIT_FAILURE;
  }
  holdall *words = holdall_empty();
  if (words == NULL) {
    holdall_dispose(&filenames);
    return EXIT_FAILURE;
  }
  //--- Commands ---------------------------------------------------------------
  while (argv[cur_arg] != NULL) {
    // String
    if (*argv[cur_arg] != '-') {
      holdall_put(words, &argv[cur_arg]);
    }
    //--- Filenames ------------------------------------------------------------
    else if (strcmp(argv[cur_arg], "-") == 0) {
      ++cur_arg;
      holdall_put(filenames, (char *) argv[cur_arg]);
    }
    //--- Options --------------------------------------------------------------
    else {
      arg_commands[command_arg] = (char *) argv[cur_arg];
    }
    ++cur_arg;
  }
  settings opt;
  manage_option(&opt, command_arg, (const char **) arg_commands);
  lidx_set_options(lid, &opt);
  holdall_apply_context(words, fun_str, funcontext, lid);
  holdall_apply_context(filenames, fun_file, funcontext, lid);
  holdall_dispose(&filenames);
  holdall_dispose(&words);
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
