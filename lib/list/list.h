#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef LIST__H
#define LIST__H

typedef struct list list;

extern list *list_empty();

extern bool list_is_empty(const list *l);

extern const void *list_add(list *l, const void *xptr);

extern const void *list_last_element(const list *l);

extern void list_dispose(list *l);

extern void list_display(list *l);

#endif
