#ifndef _ANN_H_
#define _ANN_H_

#include <stdint.h>
#include <stdio.h>

typedef uint32_t u32;

/** Note: input layer is NOT a Layer */
typedef struct ANN_t *ANN;
typedef struct ANN_config_t
{
  u32 input_count;
  u32 layer_count;
  u32 *layer_nmembs;
} ANN_config;

ANN ann_alloc (ANN_config *config);
void ann_free (ANN ann);

/**
 * Note:
 * This function does not check whether the inputs match the ann's input
 * layer. This function does not copy inputs, please make sure inputs are
 * available throughout ann's life time.
 */
void ann_hook_input (ANN ann, float *inputs);

void ann_forward (ANN ann);
void ann_fprint (FILE *file, ANN ann);

#endif /* _ANN_H_ */
