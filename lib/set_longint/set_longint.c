#include "set_longint.h"

#define FUN_FAIL -1
#define FUN_SUCC 0

typedef struct cset_longint cset_longint;

struct cset_longint {
  cset_longint *next;
  long int value;
};

struct set_longint {
  cset_longint *head;
  cset_longint *tail;
};

set_longint *set_longint_empty() {
  set_longint *sli = malloc(sizeof *sli);
  if (sli == NULL) {
    return NULL;
  }
  sli->head = NULL;
  sli->tail = NULL;
  return sli;
}

bool set_longint_is_empty(const set_longint *sli) {
  return sli->head == NULL ? true : false;
}

static const long int *set_longint_last(const set_longint *sli) {
  if (set_longint_is_empty(sli)) {
    return NULL;
  }
  return &(sli->tail->value);
}

const long int *set_longint_put(set_longint *sli, const long int *num) {
  if (!set_longint_is_empty(sli) && *set_longint_last(sli) == *num) {
    return num;
  }
  cset_longint *p = malloc(sizeof *p);
  if (p == NULL) {
    return NULL;
  }
  p->value = *num;
  p->next = NULL;
  if (set_longint_is_empty(sli)) {
    sli->head = p;
    sli->tail = p;
  } else {
    sli->tail->next = p;
    sli->tail = p;
  }
  return num;
}

void set_longint_display(set_longint *sli) {
  cset_longint *p = sli->head;
  if (p == NULL) {
    return;
  }
  printf("%ld", p->value);
  p = p->next;
  while (p != NULL) {
    printf(", %ld", p->value);
    p = p->next;
  }
}

void set_longint_dispose(set_longint *sli) {
  cset_longint *p = sli->head;
  while (p != NULL) {
    sli->head = p->next;
    free(p);
    p = sli->head;
  }
  free(sli);
  sli = NULL;
}
