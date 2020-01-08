#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef OPTION__H
#define OPTION__H

#define LOWER -1
#define AS_IS 0
#define UPPER 1

typedef struct options {
  bool sort;
  int case_word;
  char *stream_in;
  char *stream_out;
} options;

/**
 * Initialise la structure selon les arguments de la ligne de commande
 * retourne -1 en cas d'échec
 * */
int manage_option(options *opt, int argc, const char *argv[]);

/**
 * Affiche les options défini dans la structure opt
 * */
void option_debug(options *opt);
#endif
