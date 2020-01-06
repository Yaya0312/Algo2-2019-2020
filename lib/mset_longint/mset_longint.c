#include "mset_longint.h"

#define FUN_FAIL -1
#define FUN_SUCC 0

struct mset_longint {
  list *mset;
};

mset_longint *mset_longint_empty() {
  list *p = list_empty();
  if (p == NULL) {
    return NULL;
  }
  mset_longint *m = malloc(sizeof(m));
  if (m == NULL) {
    return NULL;
  }
  m->mset = p;
  return m;
}

int mset_longint_put(mset_longint *msli, long int num) {
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

void mset_longint_display(mset_longint *msli) {
  list_display(msli->mset);
}

void mset_longint_dispose(mset_longint *msliptr) {
  list_dispose(msliptr->mset);
  free(msliptr);
  msliptr = NULL;
}
