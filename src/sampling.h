#ifndef _SAMPLING_H_
#define _SAMPLING_H_

#include <stddef.h>
#include <stdint.h>

#define SAMPLING_FILL_XY(points, npoints, xmin, xmax, func)                   \
  sampling_fill_points_evenly_x (points, npoints, xmin, xmax, func);

typedef struct
{
  float x;
  float y;
} av_Point;

typedef uint32_t u32;
typedef float (*Fn2plot) (float);

float square (float x);

/** Note:
 * These functions assumes xs and ys are not NULL, and are at least *npoints
 * big. They modify *npoints to be the actual number of points generated.
 */
void sampling_fill_points_evenly_x (av_Point *points, size_t *npoints,
                                    float xmin, float xmax, Fn2plot func);

void sampling_fill_points_evenly_x_with_middle_points (av_Point *points,
                                                       size_t *npoints,
                                                       float xmin, float xmax,
                                                       Fn2plot func);

/* points utility */
float distance_squared (const av_Point *point_0, const av_Point *point_1);
void point_sort (av_Point *points, u32 npoints);

int point_compare_x (const void *point_0, const void *point_1);

#endif /* _SAMPLING_H_ */
