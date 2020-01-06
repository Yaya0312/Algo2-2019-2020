#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <stdbool.h>

#ifndef OPTION__H
#define OPTION__H

typedef struct settings {
  bool sort;
  int case_word;
  FILE *stream_in;
  FILE *stream_out;
} settings;

/**
 * Initialise la structure selon les arguments de la ligne de commande
 * retourne -1 en cas d'échec
 * */
int manage_option(settings *opt, int argc, const char *argv[]);

/**
 * Affiche les options défini dans la structure opt
 * */
void option_debug(settings *opt);
#endif
