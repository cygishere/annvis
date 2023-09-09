#include "help.h"
#include <stdlib.h>

/* activation functions */
float
relu (float x)
{
  return (x > 0 ? x : 0);
}

/**
 * Returns a float from [0, 1]
 * The random function used here is described at
 * https://c-faq.com/lib/randrange.html
 */
float
randf (void)
{
  return (float)((double)rand () / ((double)RAND_MAX + 1));
}
