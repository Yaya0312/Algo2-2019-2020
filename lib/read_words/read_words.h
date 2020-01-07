//  Partie interface du module read_words

//  Le module read_words permet d'obtenir le prochain mot d'un fichier ou d'une
// chaine de caractére. Un mot est séparé par un espace ou un signe de
// ponctuation.

#ifndef READ_WORDS__H
#define READ_WORDS__H

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_LENGTH_WORDS 63

// stocke le mot suivant de la chaine de caractére string dans la chaine de
// caractéres word et retourne le dernier caractére lu. //OK
char next_word_string(char **string, char *word);

// stocke le mot suivant du fichier file dans la chaine de caractéres word
// et retourne le dernier caractére lu. //OK
char next_word_file(FILE *file, char *word); //TODO

//TODO to remove
char next_word_stdin(FILE *file, char *word);
#endif
