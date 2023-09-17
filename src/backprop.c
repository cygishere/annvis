#include "backprop.h"
#include "ann_private.h"
#include "backprop_private.h"
#include "layer.h"
#include <stdlib.h>

void
ann_bp_enable (ANN ann)
{
  if (ann->is_backprop_enabled)
    {
      return;
    }
  u32 ix = ann->nmemb;
  for (u32 i = 0; i != ix; ++i)
    {
      Backpropagator *bpr = &ann->layers[i]->bpr;
      u32 nouts = ann->layers[i]->nouts;
      *bpr = malloc (sizeof **bpr * nouts);
      (*bpr)->deltas = malloc (sizeof (*bpr)->deltas * nouts);
      (*bpr)->zs = malloc (sizeof (*bpr)->zs * nouts);
    }
  ann->is_backprop_enabled = true;
}

void
ann_bp_disable (ANN ann)
{
  if (!ann->is_backprop_enabled)
    {
      return;
    }
  u32 ix = ann->nmemb;
  for (u32 i = 0; i != ix; ++i)
    {
      free (ann->layers[i]->bpr->deltas);
      free (ann->layers[i]->bpr->zs);
      free (ann->layers[i]->bpr);
    }
}

/* main utilities */
/** Note: This module do not own label */
void
ann_bp_hook_label (ANN ann, const float *label)
{
  ann->label = label;
}

/* Using quadratic cost for now */
void
ann_bp_find_delta_layer_last (ANN ann)
{
  Layer last_layer = ann->layers[ann->nmemb - 1];
  u32 ix = last_layer->nouts;
  /* find cost */
  float cost = 0.f;
  for (u32 i = 0; i != ix; ++i)
    {
      float diff = ann->label[i] - last_layer->outs[i];
      cost += diff * diff;
    }
  cost = cost / 2.f;
  /* backprop cost to last layer */
  for (u32 i = 0; i != ix; ++i)
    {
      last_layer->bpr->deltas[i] = (ann->label[i] - last_layer->outs[i]) * -1.f
                                   * ann_bp_d_relu (last_layer->bpr->zs[i]);
    }
}

/* TODO: This implimentation is ugly */
/* TODO: Should turn ANN into a linked list of Layer */
void
ann_bp_find_delta (u32 layer_id, ANN ann)
{
  Layer layer_prev = ann->layers[layer_id - 1];
  Layer layer = ann->layers[layer_id];
  u32 ix = layer->nouts;
  u32 jx = layer->nins;
  /* TODO */
  for (u32 j = 0; j != jx; ++j)
    {
      layer_prev->bpr->deltas[j] = 0.f;
      for (u32 i = 0; i != ix; ++i)
        {
          layer_prev->bpr->deltas[j]
              += layer->bpr->deltas[i] * layer->ws[i * layer->nins + j];
        }
      layer_prev->bpr->deltas[j] *= ann_bp_d_relu (layer_prev->bpr->zs[j]);
    }
}

/* inspection */
void
ann_bp_fprint_zs (FILE *file, ANN ann)
{
  if (!ann->is_backprop_enabled)
    {
      fprintf (file, "Backpropagation is not enabled in this ann\n");
      return;
    }
  u32 ix = ann->nmemb;
  for (u32 i = 0; i != ix; ++i)
    {
      fprintf (file, "Layer %u:\n", i);
      u32 jx = ann->layers[i]->nouts;

      fprintf (file, "zs:\n");
      float *zs = ann->layers[i]->bpr->zs;
      for (u32 j = 0; j != jx; ++j)
        {
          fprintf (file, " %f ", zs[j]);
        }
      fprintf (file, "\n");

      fprintf (file, "deltas:\n");
      float *deltas = ann->layers[i]->bpr->deltas;
      for (u32 j = 0; j != jx; ++j)
        {
          fprintf (file, " %f ", deltas[j]);
        }
      fprintf (file, "\n");
    }
}

/* misc */
float
ann_bp_d_relu (float x)
{
  return (x > 0 ? 1.f : 0.f);
}
