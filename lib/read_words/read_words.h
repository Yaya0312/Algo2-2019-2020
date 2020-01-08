//  Partie interface du module read_words

//  Le module read_words permet d'obtenir le prochain mot d'un fichier ou d'une
//    chaine de caractére. Un mot est séparé par un espace ou un signe de
//    ponctuation.

#ifndef READ_WORDS__H
#define READ_WORDS__H

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_LENGTH_WORDS 63

//  next_word_string : stocke le mot suivant de la chaine de caractère string 
//    dans la chaine de caractère word et retourne le dernier caractère lu, si
//    le mot fait plus de MAX_LENGTH_WORDS caractères, alors le mot n'est pas 
//    retourné
char next_word_string(char **string, char *word);

//  next_word_file : stocke le mot suivant du file dans la chaine de caractère 
//    word et retourne le dernier caractère lu, si le mot fait plus de 
//    MAX_LENGTH_WORDS caractères, alors le mot n'est pas retourné
char next_word_file(FILE *file, char *word);

//  next_word_stdin : stocke le mot suivant de la chaine de caractère string 
//    dans la chaine de caractère word et retourne le dernier caractère lu, si
//    le mot fait plus de MAX_LENGTH_WORDS caractères, alors le mot n'est pas 
//    retourné.
char next_word_stdin(FILE *file, char *word);
#endif
