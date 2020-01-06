#include "list.h"

typedef struct clist clist;

struct clist {
  clist *next;
  const void *value;
};

struct list {
  clist *head;
  clist *tail;
};

list *list_empty() {
  list *l = malloc(sizeof *l);
  if (l == NULL) {
    return NULL;
  }
  l->head = NULL;
  l->tail = NULL;
  return l;
}

bool list_is_empty(const list *l) {
  if (l == NULL) {
    return NULL;
  }
  return l->head == NULL ? true : false;
}

const void *list_add(list *l, const void *xptr) {
  if (xptr == NULL) {
    return NULL;
  }
  clist *p = malloc(sizeof *p);
  if (p == NULL) {
    return NULL;
  }
  p->value = xptr;
  p->next = NULL;
  if (list_is_empty(l)) {
    l->head = p;
    l->tail = p;
  } else {
    l->tail->next = p;
    l->tail = p;
  }
  return xptr;
}

const void *list_last_element(const list *l) {
  if (list_is_empty(l)) {
    return NULL;
  }
  return l->tail->value;
}

void list_dispose(list *l) {
  clist *p = l->head;
  while (p != NULL) {
    l->head = p->next;
    free(p);
    p = l->head;
  }
  free(l);
  l = NULL;
}

void list_display(list *l) {
  if (l == NULL) {
    return;
  }
  clist *p = l->head;
  if (p == NULL) {
    return;
  }
  printf("%ld", (long int) p->value);
  p = p->next;
  while (p != NULL) {
    printf(", %ld", (long int) p->value);
    p = p->next;
  }
}
