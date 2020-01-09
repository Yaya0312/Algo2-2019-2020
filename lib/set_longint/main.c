#include <stdio.h>
#include <stdbool.h>
#include "set_longint.h"

int main() {
  set_longint *sli = set_longint_empty();
  if (sli == NULL) {
    return EXIT_FAILURE;
  }
  long int num = 12;
  set_longint_put(sli, (const long int *) 12);
  num = 12;
  set_longint_put(sli, &num);
  num = 20;
  set_longint_put(sli, &num);
  num = 25;
  set_longint_put(sli, &num);
  set_longint_display(sli);
  set_longint_dispose(sli);
  return EXIT_SUCCESS;
}
