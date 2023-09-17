#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ann.h"
#include "backprop.h"

int
main (void)
{
  /* use a fixed seed now for testing */
  srand (777);

  u32 neuron_counts[] = { 2, 3, 1 };
  ANN_config config
      = { .input_count = 1, .layer_count = 3, .layer_nmembs = neuron_counts };
  ANN ann = ann_alloc (&config);
  ann_bp_enable (ann);

  float input[] = { 4.3f };
  float label[] = { 4.3f * 4.3f };
  ann_hook_input (ann, input);
  ann_bp_hook_label (ann, label);
  ann_forward (ann);
  ann_bp_find_delta_layer_last (ann);
  ann_bp_find_delta (2, ann);
  ann_bp_find_delta (1, ann);

  ann_fprint (stdout, ann);
  ann_bp_fprint_zs (stdout, ann);

  ann_bp_disable (ann);
  ann_free (ann);
}
