#ifndef _BACKPROP_PRIVATE_H_
#define _BACKPROP_PRIVATE_H_

typedef struct Backpropagator_t *Backpropagator;

struct Backpropagator_t
{
  float *zs;     /* num of zs = layer->nout */
  float *deltas; /* num of deltas = layer->nout */
};

#endif /* _BACKPROP_PRIVATE_H_ */
