#ifndef _ANN_PRIVATE_H_
#define _ANN_PRIVATE_H_

#include "layer.h"
#include <stdbool.h>

struct ANN_t
{
  u32 nmemb;
  Layer *layers;
  bool is_backprop_enabled;
  const float *label; /* ann do not own label */
};

#endif /* _ANN_PRIVATE_H_ */
