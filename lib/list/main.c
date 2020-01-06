#include <stdio.h>
#include <stdbool.h>
#include "list.h"

int main() {
  list *li = list_empty();
  if (li == NULL) {
    return EXIT_FAILURE;
  }
  list_add(li, (const void *) 12);
  list_add(li, (const void *) 14);
  list_add(li, (const void *) 14);
  list_add(li, (const void *) 15);
  list_display(li);
  printf("\nlast element : %ld\n", (long int) list_last_element(li));
  list_dispose(li);
  return EXIT_SUCCESS;
}
