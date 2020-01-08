#include <stdio.h>
#include <stdbool.h>
#include "setb.h"

int main() {
  setb *msb = setb_empty(6);
  if (msb == NULL) {
    return EXIT_FAILURE;
  }
  for (int i = 0; i < 10; ++i) {
    if ((i % 2) == 0) {
      setb_put(msb, i);
    }
  }
  setb_display(msb);
  setb_dispose(&msb);
  return EXIT_SUCCESS;
}
