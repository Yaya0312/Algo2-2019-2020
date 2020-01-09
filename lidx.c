#include "holdall.h"
#include "hashtable.h"
#include "option.h"
#include "read_words.h"
#include "setb.h"
#include "lidx.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "set_longint.h"

#define FUN_FAIL -1
#define FUN_SUCC 0
#define MAX_LENGTH_WORDS 63
#define WORD_LIMIT -2
#define MAX_LEX 2

struct lidx {
  hashtable *data;
  holdall *words;
  holdall *filenames;
  options *options;
};

typedef struct {
  set_longint *lines;
  setb *is_in;
} ht_val;

static int display_files(const char *s);
static void *print_line(hashtable *ht, char *word);
static int loop(void *word, void *res);
static int rfree(void *ptr);
static size_t str_hashfun(const char *s);
static int add_word(lidx *lid, const char *word, int file_pos);
static void update_line(lidx *lex, long int line, char *word);
static void *free_value_hashatbale(hashtable *ht, char *word);
static void update_case(int opp, char *word);

lidx *lidx_empty() {
  lidx *lid = malloc(sizeof(*lid));
  if (lid == NULL) {
    return NULL;
  }
  //data
  lid->data = hashtable_empty((int (*)(const void *, const void *))strcoll,
          (size_t (*)(const void *))str_hashfun);
  //words
  lid->words = holdall_empty();
  //words
  lid->filenames = holdall_empty();
  //error
  if (lid->data == NULL || lid->words == NULL || lid->filenames == NULL) {
    hashtable_dispose(&(lid->data));
    holdall_dispose(&(lid->words));
    holdall_dispose(&(lid->filenames));
    return NULL;
  }
  return lid;
}

int lidx_add_file(lidx *lid, char *path) {
  if (holdall_put(lid->filenames, path) != 0) {
    return FUN_FAIL;
  }
  size_t counter = holdall_count(lid->filenames);
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    return FUN_FAIL;
  }
  char word[MAX_LENGTH_WORDS];
  char c;
  while (true) {
    c = next_word_file(file, word);
    if (strlen(word) > 0 && c != WORD_LIMIT) {
      update_case(lid->options->case_word, word);
      add_word(lid, word, (int) counter);
    }
    if (c == EOF) {
      break;
    }
  }
  fclose(file);
  return FUN_SUCC;
}

int lidx_add_string(lidx *lid, const char **s) {
  if (strlen(*s) == 0) {
    fprintf(stderr, "*** No word.\n");
    exit(EXIT_FAILURE);
  }
  char word[MAX_LENGTH_WORDS];
  char c;
  while (true) {
    c = next_word_string((char **) s, word);
    if (strlen(word) > 0 && c != WORD_LIMIT) {
      update_case(lid->options->case_word, word);
      add_word(lid, word, 0);
    }
    if (c == EOF || c == '\n' || c == '\0') {
      break;
    }
  }
  return FUN_SUCC;
}

int lidx_add_stdin(lidx *lid, FILE *stream) {
  if (stream == NULL || lid == NULL) {
    return FUN_FAIL;
  }
  char word[MAX_LENGTH_WORDS];
  char c;
  long int line = 1;
  while (true) {
    c = next_word_stdin(stream, word);
    if (strlen(word) > 0 && c != WORD_LIMIT) {
      if (c == '\n') {
        ++line;
      } else {
        update_case(lid->options->case_word, word);
        update_line(lid, line, word);
      }
    }
    if (c == EOF) {
      break;
    }
  }
  return FUN_SUCC;
}

void lidx_print(lidx *lid) {
  //apply options
  if (lid->options->sort) {
    holdall_sort(lid->words, (int (*)(const void *, const void *))strcoll);
  }
  //header
  printf("\t\t");
  holdall_apply(lid->filenames, (int (*)(void *))display_files);
  printf("\n");
  //body
  holdall_apply_context(lid->words, (int (*)(void *, void *))loop,
      (void *(*)(void *, void *))print_line, lid->data);
}

void lidx_set_options(lidx *lid, options *opts) {
  lid->options = opts;
}

void lidx_dispose(lidx *lid) {
  //free value hastable
  holdall_apply_context(lid->words, (int (*)(void *, void *))loop,
      (void *(*)(void *, void *))free_value_hashatbale, lid->data);
  //free
  holdall_apply(lid->words, rfree);
  holdall_dispose(&(lid->words));
  holdall_dispose(&(lid->filenames));
  hashtable_dispose(&(lid->data));
  free(lid);
  lid = NULL;
}

//------------------ Fonctions outils pour le foure tout -----------------------

static int display_files(const char *s) {
  return printf("%s\t", s) < 0;
}

static void *print_line(hashtable *ht, char *word) {
  ht_val *data = (ht_val *) hashtable_search(ht, word);
  hashtable_search(ht, word);
  printf("%s", word);
  setb_display(data->is_in);
  set_longint_display(data->lines);
  printf("\n");
  return FUN_SUCC;
}

static int loop(void *word, void *res) {
  return word == NULL && res ? FUN_FAIL : FUN_SUCC;
}

static int rfree(void *ptr) {
  free(ptr);
  return 0;
}

static size_t str_hashfun(const char *s) {
  size_t h = 0;
  for (const unsigned char *p = (const unsigned char *) s; *p != '\0'; ++p) {
    h = 37 * h + *p;
  }
  return h;
}

//--- Ajout mot && mise à jour ligne -------------------------------------------
static int add_word(lidx *lid, const char *word, int file_pos) {
  ht_val *cptr = (ht_val *) hashtable_search(lid->data, word);
  // not exist
  if (cptr == NULL) {
    char *s = malloc(sizeof(char) * MAX_LENGTH_WORDS);
    memcpy(s, word, MAX_LENGTH_WORDS);
    if (holdall_put(lid->words, (char *) s) != 0) {
      goto error_capacity;
    }
    ht_val *p = malloc(sizeof(*p));
    if (p == NULL) {
      goto error_capacity;
    }
    p->lines = set_longint_empty();
    if (p->lines == NULL) {
      return FUN_FAIL;
    }
    p->is_in = setb_empty(MAX_LEX);
    if (p->is_in == NULL) {
      return FUN_FAIL;
    }
    if (hashtable_add(lid->data, s, p) == NULL) {
      free(p);
      goto error_capacity;
    }
    setb_put(p->is_in, file_pos);
  } else {
    setb_put(cptr->is_in, file_pos);
  }
  int r = FUN_SUCC;
  goto end;
error_capacity:
  r = FUN_FAIL;
end:
  return r;
}

static void update_line(lidx *lex, long int line, char *word) {
  ht_val *p = (ht_val *) hashtable_search(lex->data, word);
  if (p != NULL) {
    set_longint_put(p->lines, &line);
  }
}

static void *free_value_hashatbale(hashtable *ht, char *word) {
  ht_val *p = (ht_val *) hashtable_search(ht, word);
  set_longint_dispose(p->lines);
  setb_dispose(&(p->is_in));
  free(p);
  p = NULL;
  return NULL;
}

//--- Change case --------------------------------------------------------------
void apply_string(char *str, int (*fun)(int)) {
  while (*str != '\0' && *str != EOF) {
    *str = (char) fun(*str);
    str = str + 1;
  }
}

static void to_upper_string(char *str) {
  apply_string(str, toupper);
}

static void to_lower_string(char *str) {
  apply_string(str, tolower);
}

static void update_case(int opp, char *word) {
  switch (opp) {
    case LOWER:
      to_lower_string(word);
      break;
    case UPPER:
      to_upper_string(word);
  }
}
