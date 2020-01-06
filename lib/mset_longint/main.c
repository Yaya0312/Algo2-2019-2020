#include <stdio.h>
#include <stdbool.h>
#include "mset_longint.h"

int main() {
  mset_longint *msli = mset_longint_empty();
  if (msli == NULL) {
    return EXIT_FAILURE;
  }
  mset_longint_put(msli, 12);
  mset_longint_put(msli, 18);
  mset_longint_put(msli, 20);
  mset_longint_put(msli, 25);
  mset_longint_display(msli);
  mset_longint_dispose(msli);
  return EXIT_SUCCESS;
}
