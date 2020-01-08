#include "setb.h"

#define FUN_SUCC 0
#define FUN_FAIL -1

#define ERR_GREATER_THAN_MAX -2
#define ERR_LOWER_THAN_LAST_VALUE -3
#define ERR_CAPACITY_MEMORY -4

typedef struct csetb csetb;

struct setb {
  csetb *head;
  csetb *tail;
  int max;
};

struct csetb {
  int value;
  csetb *next;
};

setb *setb_empty(int max) {
  setb *p = malloc(sizeof *p);
  if (p == NULL) {
    return NULL;
  }
  p->max = max;
  p->head = NULL;
  p->tail = NULL;
  return p;
}

int setb_put(setb *msli, int num) {
  if (msli == NULL) {
    return FUN_FAIL;
  }
  if (num > setb_max(msli)) {
    return ERR_GREATER_THAN_MAX;
  }
  if (msli->tail != NULL) {
    if (num < msli->tail->value) {
      return ERR_LOWER_THAN_LAST_VALUE;
    }
  }
  csetb *p = malloc(sizeof *p);
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

void setb_display(setb *msli) {
  if (msli == NULL) {
    return;
  }
  int counter = 0;
  csetb *p = msli->head;
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

int setb_max(setb *msbprt) {
  if (msbprt == NULL) {
    return FUN_FAIL;
  }
  return msbprt->max;
}

void setb_dispose(setb **msliptr) {
  if (*msliptr == NULL) {
    return;
  }
  csetb *p = (*msliptr)->head;
  while (p != NULL) {
    csetb *t = p;
    p = p->next;
    free(t);
  }
  free(*msliptr);
  *msliptr = NULL;
}
