//Partie interface du module option
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef OPTION__H
#define OPTION__H

//  Le module option permet la gestion des différentes options sur la ligne de
//    de commande

#define LOWER -1
#define AS_IS 0
#define UPPER 1

//  Permet de stocker les différentes options
typedef struct options {
  bool sort;
  int case_word;
  char *stream_in;
  char *stream_out;
} options;

//  manage_option : Initialise la structure opt selon les arguments argc et argv
void manage_option(options *opt, int argc, const char *argv[]);

//  option_debug : affiche sur la sortie standard les options fournis par le
//    paramètre opt sous une forme facilement comprehensible
void option_debug(options *opt);
#endif
