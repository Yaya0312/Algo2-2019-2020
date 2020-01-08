#include "set_longint.h"

#define FUN_FAIL -1
#define FUN_SUCC 0

struct set_longint {
  list *mset;
};

set_longint *set_longint_empty() {
  list *p = list_empty();
  if (p == NULL) {
    return NULL;
  }
  set_longint *m = malloc(sizeof(m));
  if (m == NULL) {
    return NULL;
  }
  m->mset = p;
  return m;
}

int set_longint_put(set_longint *msli, long int num) {
  if (msli == NULL) {
    return FUN_FAIL;
  }
  if (list_last_element(msli->mset) != (const void *) num) {
    if (list_add(msli->mset, (const void *) num) == NULL) {
      return FUN_FAIL;
    }
  }
  return FUN_SUCC;
}

void set_longint_display(set_longint *msli) {
  list_display(msli->mset);
}

void set_longint_dispose(set_longint *msliptr) {
  list_dispose(msliptr->mset);
  free(msliptr);
  msliptr = NULL;
}
