#include "window.h"
#include "sampling.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

static struct Window_t
{
  u32 width;
  u32 height;

  size_t npoints;
  float *xs;
  float *ys;

  /* axis bounds */
  float xmin;
  float xmax;
  float ymin;
  float ymax;

} win;

void
window_init (u32 width, u32 height, const char *name)
{
  win.width = width;
  win.height = height;

  /* viewport size */
  win.xmin = -10.f;
  win.xmax = 10.f;
  win.ymin = 0.f;
  win.ymax = 20.f;

  win.npoints = 401;

  win.xs = malloc (sizeof win.xs * win.npoints);
  win.ys = malloc (sizeof win.ys * win.npoints);
  av_Point points[win.npoints];
  SAMPLING_FILL_XY (points, &win.npoints, win.xmin, win.xmax, square);
  for (u32 i = 0; i != win.npoints; ++i)
    {
      win.xs[i] = points[i].x;
      win.ys[i] = points[i].y;
    }

  SetConfigFlags (FLAG_MSAA_4X_HINT);
  InitWindow (width, height, name);
  SetExitKey (KEY_Q);
  SetTargetFPS (60);
}

void
window_quit (void)
{
  /* HACK: should not malloc, hook ptr instead */
  free (win.xs);
  free (win.ys);

  CloseWindow ();
}

void
window_run (void)
{
  while (!WindowShouldClose ())
    {
      /* handle events */

      /* drawing */
      BeginDrawing ();

      ClearBackground (BLACK);
      for (size_t i = 0; i != win.npoints; ++i)
        {
          /* TODO Should keep the grid ratio to dx:dy = 1:1 */
          if (window_is_point_in_bounds (i))
            {
              Vector2 point = { .x = (win.xs[i] - win.xmin) * win.width
                                     / (win.xmax - win.xmin),
                                .y = win.height
                                     - (win.ys[i] - win.ymin) * win.height
                                           / (win.ymax - win.ymin) };
              DrawCircleV (point, 3, GREEN);
            }
        }

      EndDrawing ();
    }
}

int
window_is_point_in_bounds (u32 point_id)
{
  return ((win.xs[point_id] >= win.xmin) || (win.xs[point_id] <= win.xmax)
          || (win.ys[point_id] >= win.ymin) || (win.ys[point_id] <= win.ymax));
}
