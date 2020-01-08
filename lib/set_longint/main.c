#include <stdio.h>
#include <stdbool.h>
#include "set_longint.h"

int main() {
  set_longint *msli = set_longint_empty();
  if (msli == NULL) {
    return EXIT_FAILURE;
  }
  set_longint_put(msli, 12);
  set_longint_put(msli, 18);
  set_longint_put(msli, 20);
  set_longint_put(msli, 25);
  set_longint_display(msli);
  set_longint_dispose(msli);
  return EXIT_SUCCESS;
}
