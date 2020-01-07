#include "read_words.h"

#define FUN_SUCC 0
#define FUN_FAIL -1
#define WORD_LIMIT -2

// TODO fusionner avec next_word_file grace la fonction fmemopen qui converti
// une chaine de caractére en fichier
char next_word_string(char **string, char *word) {
  int count = 0;
  char c;
  while ((c = **string)) {
    if (count > MAX_LENGTH_WORDS) {
      while ((c = **string)) {
        if (c == '\0' || c == EOF || isspace(c) || ispunct(c)) {
          return WORD_LIMIT;
        }
        ++(*string);
      }
      return WORD_LIMIT;
    }
    if (c == '\0' || isspace(c) || ispunct(c)) {
      break;
    }
    *word = (char) c;
    ++word;
    ++(*string);
    ++count;
  }
  *word = '\0';
  ++(*string);
  return c;
}

char next_word_file(FILE *file, char *word) {
  int count = 0;
  char c;
  while ((c = (char) fgetc(file))) {
    if (count > MAX_LENGTH_WORDS) {
      while ((c = (char) fgetc(file))) {
        if (c == '\0' || c == EOF || isspace(c) || ispunct(c)) {
          return WORD_LIMIT;
        }
      }
      return WORD_LIMIT;
    }
    if (c == '\0' || c == EOF || isspace(c) || ispunct(c)) {
      break;
    }
    *word = (char) c;
    ++word;
    ++count;
  }
  *word = '\0';
  return c;
}

char next_word_stdin(FILE *file, char *word) {
  int count = 0;
  char c;
  while ((c = (char) fgetc(file))) {
    if (count > MAX_LENGTH_WORDS) {
      while ((c = (char) fgetc(file))) {
        if (c == '\0' || c == EOF || isspace(c) || ispunct(c)) {
          return WORD_LIMIT;
        }
      }
      return WORD_LIMIT;
    }
    if (c == '\n') {
      return c;
    }
    if (c == '\0' || c == EOF || isspace(c) || ispunct(c)) {
      break;
    }
    *word = (char) c;
    ++word;
    ++count;
  }
  *word = '\0';
  return c;
}
