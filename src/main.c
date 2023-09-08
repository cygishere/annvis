#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ann.h"

int
main (void)
{
  u32 neuron_counts[] = { 2, 3, 1 };
  ANN_config config
      = { .input_count = 1, .layer_count = 3, .layer_nmembs = neuron_counts };
  ANN ann = ann_alloc (&config);

  float input = 4.3f;
  ann_hook_input (ann, &input);
  ann_fprint (stdout, ann);

  ann_free (ann);
}
