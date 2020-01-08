#include <stdio.h>
#include <stdbool.h>
#include "set_longint.h"

int main() {
  set_longint *sli = set_longint_empty();
  if (sli == NULL) {
    return EXIT_FAILURE;
  }
  set_longint_put(sli, 12);
  set_longint_put(sli, 18);
  set_longint_put(sli, 20);
  set_longint_put(sli, 25);
  set_longint_display(sli);
  set_longint_dispose(sli);
  return EXIT_SUCCESS;
}
