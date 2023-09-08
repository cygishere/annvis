#include "ann.h"
#include "layer.h"
#include <stdlib.h>

struct ANN_t
{
  u32 nmemb;
  Layer *layers;
};

ANN
ann_alloc (ANN_config *config)
{
  ANN ann = malloc (sizeof *ann);
  ann->nmemb = config->layer_count;
  ann->layers = malloc (sizeof *ann->layers * ann->nmemb);
  ann->layers[0] = layer_alloc (config->layer_nmembs[0], config->input_count);
  for (u32 i = 1; i != ann->nmemb; ++i)
    {
      ann->layers[i]
          = layer_alloc (config->layer_nmembs[i], config->layer_nmembs[i - 1]);
    }
  return ann;
}

void
ann_free (ANN ann)
{
  for (u32 i = 0; i != ann->nmemb; ++i)
    {
      layer_free (ann->layers[i]);
    }
  free (ann->layers);
  free (ann);
}

void
ann_hook_input (ANN ann, float *inputs)
{
  layer_hook_input (ann->layers[0], inputs);
}

void
ann_forward (ANN ann)
{
  //  layer_calc (ann->layers[1]);
}

void
ann_fprint (FILE *file, ANN ann)
{
  size_t ann_size = 0;
  fprintf (file, "Summary of structure:\n");
  for (u32 i = 0; i != ann->nmemb; ++i)
    {
      fprintf (file, "Layer %u: ", i);
      layer_fprintf (file, ann->layers[i]);
      fprintf (file, "\n");
      ann_size += layer_get_size (ann->layers[i]);
    }
  fprintf (file, "Total size: %zu B, or %.2f KiB, or %.4f MiB\n", ann_size,
           (double)ann_size / 1024, (double)ann_size / 1024 / 1024);
}
