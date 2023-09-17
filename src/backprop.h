/**
 * This header enhance the "ANN" introduced in "ann.h",
 * giving it the ability to do backpropagation.
 */

#ifndef _BACKPROP_H_
#define _BACKPROP_H_

#include "ann.h"
#include <stdio.h>

/** Note: you should always pair these two calls */
void ann_bp_enable (ANN ann);
void ann_bp_disable (ANN ann);

/* main utilities */
/** Note: This module do not own labels */
void ann_bp_hook_label (ANN ann, const float *labels);
/* The four equations */
void ann_bp_find_delta_layer_last (ANN ann);
void ann_bp_find_delta (u32 layer_id, ANN ann);

/* inspection */
void ann_bp_fprint_zs (FILE *file, ANN ann);

/* misc */
float ann_bp_d_relu (float x);

#endif /* _BACKPROP_H_ */
