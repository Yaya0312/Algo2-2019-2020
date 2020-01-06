#include <stdio.h>
#include <stdbool.h>
#include "read_words.h"

#define EXIT_FAILURE -1
#define EXIT_SUCCESS 1

int main() {
  const char *string = (const char *) "la pomme bleu.";
  char word[MAX_LENGTH_WORDS];
  char c;
  printf("*** String : print\n");
  while (true) { //A optimiser (voir Q.16)
    c = next_word_string((char **) &string, word);
    if (strlen((char *) word) > 0) {
      printf("%s\n", word);
    }
    if (c == '\n' || c == '\0') {
      break;
    }
  }
  //Fichier
  printf("*** File : print\n");
  FILE *file = fopen("main.c", "r");
  if (file == NULL) {
    return EXIT_FAILURE;
  }
  while (true) {
    c = next_word_file(file, word);
    if (strlen(word) > 0) {
      printf("%s\n", word);
    }
    if (c == EOF) {
      break;
    }
  }
  fclose(file);
  //Entrée standard
  printf("*** Stdin : print\n");
  while (true) {
    c = next_word_stdin(stdin, word);
    if (strlen(word) > 0) {
      printf("%s\n", word);
    }
    if (c == '\n') {
      break;
    }
  }
  return EXIT_SUCCESS;
}
