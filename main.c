#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "lidx.h"
#include "option.h"
#include "locale.h"
#include "holdall.h"

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Nombre d'arguments invalide.\n");
    exit(EXIT_FAILURE);
  }
  //--- Init var ---------------------------------------------------------------
  setlocale(LC_COLLATE, "");
  int cur_arg = 1;
  int command_arg = 1;
  const char *arg_commands[argc];
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
      command_arg = command_arg + 1;
      if (strcmp("-i", argv[cur_arg]) == 0) {
        ++cur_arg;
        if (cur_arg >= argc) {
          exit(EXIT_FAILURE);
        }
        arg_commands[command_arg] = (char *) argv[cur_arg];
        command_arg = command_arg + 1;
      }
    }
    ++cur_arg;
  }
  options opt;
  manage_option(&opt, command_arg, (const char **) arg_commands);
  lidx *lid = lidx_empty(words, filenames, &opt);
  if (lid == NULL) {
    return EXIT_FAILURE;
  }
  holdall_dispose(&filenames);
  holdall_dispose(&words);
  if (opt.stream_in == NULL) {
    lidx_add_stdin(lid, stdin);
  } else {
    FILE *file = fopen(opt.stream_in, "r");
    lidx_add_stdin(lid, file);
    fclose(file);
  }
  lidx_print(lid);
  lidx_dispose(lid);
  return EXIT_SUCCESS;
}
