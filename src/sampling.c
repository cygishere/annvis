#include "sampling.h"
#include <stdio.h>
#include <stdlib.h>

float
square (float x)
{
  return x * x;
}

void
sampling_fill_points_evenly_x (av_Point *points, size_t *npoints, float xmin,
                               float xmax, Fn2plot func)
{
  float span = xmax - xmin;
  for (size_t i = 0; i != *npoints; ++i)
    {
      points[i].x = span / (*npoints + 1) * (i + 1) + xmin;
      points[i].y = func (points[i].x);
    }
}

void
sampling_fill_points_evenly_x_with_middle_points (av_Point *points,
                                                  size_t *npoints, float xmin,
                                                  float xmax, Fn2plot func)
{
  /* TODO */
}

/* points utility */
float
distance_squared (const av_Point *point_0, const av_Point *point_1)
{
  float dx = point_0->x - point_1->x;
  float dy = point_0->y - point_1->y;
  return dx * dx + dy * dy;
}

void
point_sort (av_Point *points, u32 npoints)
{
  qsort (points, (size_t)npoints, sizeof *points, point_compare_x);
}

int
point_compare_x (const void *point_0, const void *point_1)
{
  const av_Point *p0 = point_0;
  const av_Point *p1 = point_1;
  if (p0->x < p1->x)
    {
      return -1;
    }
  else if (p0->x == p1->x)
    {
      return 0;
    }
  else
    {
      return 1;
    }
}
