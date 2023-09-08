#include "layer.h"
#include <stdlib.h>

Layer
layer_alloc (u32 nthis, u32 nprev)
{
  Layer layer = malloc (sizeof *layer);
  layer->nas = nthis;
  layer->ninputs = nprev;
  layer->nws = layer->nas * layer->ninputs;
  layer->nbs = layer->nas;
  layer->as = malloc (sizeof *layer->as * nthis);
  layer->ws = malloc (sizeof *layer->ws * layer->nws);
  layer->bs = malloc (sizeof *layer->bs * layer->nbs);
  return layer;
}

void
layer_free (Layer layer)
{
  free (layer->as);
  free (layer->ws);
  free (layer->bs);
  free (layer);
}

void
layer_hook_input (Layer layer, float *inputs)
{
  layer->inputs = inputs;
}

size_t
layer_get_size (Layer layer)
{
  return (sizeof *layer->as * layer->nas) + (sizeof *layer->ws * layer->nws)
         + (sizeof *layer->bs * layer->nbs);
}

void
layer_calc (Layer layer)
{
}

void
layer_fprintf (FILE *file, Layer layer)
{
  fprintf (file, "#ins: %u #outs: %u\t#weights: %u x %u\t#biases: %u",
           layer->ninputs, layer->nas, layer->nas, layer->ninputs, layer->nbs);
}
