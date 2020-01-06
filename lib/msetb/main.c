#include <stdio.h>
#include <stdbool.h>
#include "msetb.h"

int main() {
  msetb *msb = msetb_empty(6);
  if (msb == NULL) {
    return EXIT_FAILURE;
  }
  for (int i = 0; i < 10; ++i) {
    if ((i % 2) == 0) {
      msetb_put(msb, i);
    }
  }
  msetb_display(msb);
  msetb_dispose(&msb);
  return EXIT_SUCCESS;
}
