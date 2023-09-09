#ifndef _LAYER_H_
#define _LAYER_H_

#include <stdint.h>
#include <stdio.h>

typedef uint32_t u32;
typedef struct Layer_t *Layer;

/**
 * Note:
 * Acturally, the input layer should not be a Layer
 */

struct Layer_t
{
  u32 nins;         /* number of neurons in the previous layer */
  const float *ins; /* neurons from the previous layer (inputs) */

  u32 nouts;   /* number of neurons in this layer */
  u32 nws;     /* number of weights in this layer */
  u32 nbs;     /* number of biases in this layer */
  float *outs; /* output neurons */
  float *ws;   /* weights */
  float *bs;   /* biases */
};

/** Note: The input layer is not alloced, please hook input before forward */
Layer layer_alloc (u32 nthis, u32 nprev);
void layer_free (Layer layer);

void layer_init (Layer layer);

/** Note: This function does not check whether layer is input layer or not */
void layer_hook_input (Layer layer, float *inputs);
/** Note: This function does not check whether the dimensions of layer are
 * matched */
void layer_hook_layer (Layer layer, Layer layer_prev);
/** size in bytes (char) */
size_t layer_get_size (Layer layer);
/** Note: This function does not check whether the dimensions are matched */
void layer_calc (Layer layer);

void layer_fprint_structure (FILE *file, Layer layer);
void layer_fprint_ptrs (FILE *file, Layer layer);
void layer_fprint_arrays (FILE *file, Layer layer); /* TODO */

#endif /* _LAYER_H_ */
