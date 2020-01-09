#include "read_words.h"

#define FUN_SUCC 0
#define FUN_FAIL -1
#define WORD_LIMIT -2

#define NEXT_WORD_F(STDIN)                                                     \
  int count = 0;                                                               \
  char c;                                                                      \
  while ((c = (char) fgetc(file))) {                                           \
    if (count > MAX_LENGTH_WORDS) {                                            \
      while ((c = (char) fgetc(file))) {                                       \
        if (!isalnum(c)) {                                                     \
          return WORD_LIMIT;                                                   \
        }                                                                      \
      }                                                                        \
      return WORD_LIMIT;                                                       \
    }                                                                          \
    if (STDIN) {                                                               \
      if (c == '\n') {                                                         \
        return c;                                                              \
      }                                                                        \
    }                                                                          \
    if (!isalnum(c)) {                                                         \
      break;                                                                   \
    }                                                                          \
    *word = (char) c;                                                          \
    ++word;                                                                    \
    ++count;                                                                   \
  }                                                                            \
  *word = '\0';                                                                \
  return c;

#define FILE_TYPE 0

char next_word_file(FILE *file, char *word) {
  NEXT_WORD_F(FILE_TYPE)
}

char next_word_string(char **string, char *word) {
  int count = 0;
  char c;
  while ((c = (char) **string)) {
    if (count > MAX_LENGTH_WORDS) {
      while ((c = (char) **string)) {
        if (!isalnum(c)) {
          return WORD_LIMIT;
        }
        ++(*string);
      }
      return WORD_LIMIT;
    }
    if (!isalnum(c)) {
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

#define STDIN 1

char next_word_stdin(FILE *file, char *word) {
  NEXT_WORD_F(STDIN)
}
