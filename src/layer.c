#include "layer.h"
#include "help.h"
#include <stdlib.h>

Layer
layer_alloc (u32 nthis, u32 nprev)
{
  Layer layer = malloc (sizeof *layer);
  layer->nouts = nthis;
  layer->nins = nprev;
  layer->nws = layer->nouts * layer->nins;
  layer->nbs = layer->nouts;
  layer->outs = malloc (sizeof *layer->outs * nthis);
  layer->ws = malloc (sizeof *layer->ws * layer->nws);
  layer->bs = malloc (sizeof *layer->bs * layer->nbs);
  return layer;
}

void
layer_free (Layer layer)
{
  free (layer->outs);
  free (layer->ws);
  free (layer->bs);
  free (layer);
}

void
layer_init (Layer layer)
{
  /* fill weights and bias with random values */
  for (u32 i = 0; i != layer->nws; ++i)
    {
      layer->ws[i] = randf ();
    }
  for (u32 i = 0; i != layer->nbs; ++i)
    {
      layer->bs[i] = randf ();
    }
}

void
layer_hook_input (Layer layer, float *inputs)
{
  layer->ins = inputs;
}

void
layer_hook_layer (Layer layer, Layer layer_prev)
{
  layer->ins = layer_prev->outs;
}

size_t
layer_get_size (Layer layer)
{
  return (sizeof *layer->outs * layer->nouts)
         + (sizeof *layer->ws * layer->nws) + (sizeof *layer->bs * layer->nbs);
}

void
layer_calc (Layer layer)
{
  float *weights = layer->ws;
  /* Matrix calculation, should be extracted in the future */
  for (u32 r = 0; r != layer->nouts; ++r)
    {
      float out = 0.f;
      for (u32 c = 0; c != layer->nins; ++c)
        {
          out += layer->ins[c] * weights[c];
        }
      layer->outs[r] = relu (out + layer->bs[r]);
      weights += layer->nins;
    }
}

void
layer_fprint_structure (FILE *file, Layer layer)
{
  fprintf (file, "#ins: %u\t#outs: %u\t#weights: %u x %u\t#biases: %u",
           layer->nins, layer->nouts, layer->nouts, layer->nins, layer->nbs);
}

void
layer_fprint_ptrs (FILE *file, Layer layer)
{
  fprintf (file, "&ins: %p\t&outs: %p\t&ws: %p\t&bs: %p", (void *)layer->ins,
           (void *)layer->outs, (void *)layer->ws, (void *)layer->bs);
}

void
layer_fprint_arrays (FILE *file, Layer layer)
{
  fprintf (file, "ws:\n");
  for (u32 r = 0; r != layer->nouts; ++r)
    {
      for (u32 c = 0; c != layer->nins; ++c)
        {
          fprintf (file, " %8f ", layer->ws[r * layer->nins + c]);
        }
      fprintf (file, "\n");
    }

  fprintf (file, "bs:\n");
  for (u32 i = 0; i != layer->nbs; ++i)
    {
      fprintf (file, " %8f ", layer->bs[i]);
    }
  fprintf (file, "\n");

  fprintf (file, "outs:\n");
  for (u32 i = 0; i != layer->nouts; ++i)
    {
      fprintf (file, " %8f ", layer->outs[i]);
    }
  fprintf (file, "\n");
}
