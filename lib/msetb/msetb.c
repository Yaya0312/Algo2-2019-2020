#include "msetb.h"

#define FUN_SUCC 0
#define FUN_FAIL -1

#define ERR_GREATER_THAN_MAX -2
#define ERR_LOWER_THAN_LAST_VALUE -3
#define ERR_CAPACITY_MEMORY -4

typedef struct cmsetb cmsetb;

struct msetb {
  cmsetb *head;
  cmsetb *tail;
  int max;
};

struct cmsetb {
  int value;
  cmsetb *next;
};

msetb *msetb_empty(int max) {
  msetb *p = malloc(sizeof *p);
  if (p == NULL) {
    return NULL;
  }
  p->max = max;
  p->head = NULL;
  p->tail = NULL;
  return p;
}

int msetb_put(msetb *msli, int num) {
  if (msli == NULL) {
    return FUN_FAIL;
  }
  if (num > msetb_max(msli)) {
    return ERR_GREATER_THAN_MAX;
  }
  if (msli->tail != NULL) {
    if (num < msli->tail->value) {
      return ERR_LOWER_THAN_LAST_VALUE;
    }
  }
  cmsetb *p = malloc(sizeof *p);
  if (p == NULL) {
    return ERR_CAPACITY_MEMORY;
  }
  p->next = NULL;
  p->value = num;
  if (msli->tail == NULL) {
    msli->tail = p;
  } else {
    msli->tail->next = p;
    msli->tail = msli->tail->next;
  }
  if (msli->head == NULL) {
    msli->head = msli->tail;
  }
  return FUN_SUCC;
}

void msetb_display(msetb *msli) {
  if (msli == NULL) {
    return;
  }
  int counter = 0;
  cmsetb *p = msli->head;
  while (counter <= msli->max) {
    printf("\t");
    if (p != NULL && counter == p->value) {
      printf("x");
      p = p->next;
    }
    counter = counter + 1;
  }
  printf("\t");
}

int msetb_max(msetb *msbprt) {
  if (msbprt == NULL) {
    return FUN_FAIL;
  }
  return msbprt->max;
}

void msetb_dispose(msetb **msliptr) {
  if (*msliptr == NULL) {
    return;
  }
  cmsetb *p = (*msliptr)->head;
  while (p != NULL) {
    cmsetb *t = p;
    p = p->next;
    free(t);
  }
  free(*msliptr);
  *msliptr = NULL;
}
