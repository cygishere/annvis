#include "window.h"
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

  win.xmin = -10.f;
  win.xmax = 10.f;
  win.ymin = 0.f;
  win.ymax = 20.f;

  win.npoints = 401;

  /* HACK: should not malloc, hook ptr instead */
  float xs[win.npoints];
  float ys[win.npoints];
  xs[0] = win.xmin;
  for (u32 i = 1; i != win.npoints; ++i)
    {
      /* TODO */
      float der = 2.f * xs[i - 1];
      xs[i] = xs[i - 1] + 0.5f / sqrtf (1.f + der * der);
      printf ("der: %f, x: %f, dist: %f, cos: %f\n", der, xs[i],
              sqrtf (powf (xs[i] - xs[i - 1], 2.f)
                     + powf (powf (xs[i], 2.f) - powf (xs[i - 1], 2.f), 2.f)),
              1.f / sqrtf (1.f + der * der));
      /* xs[i] = (4.4f + 4.4f) / (win.npoints + 1) * (i + 1) - 4.4f; */
    }
  for (u32 i = 0; i != win.npoints; ++i)
    {
      ys[i] = xs[i] * xs[i];
    }
  win.xs = malloc (sizeof win.xs * win.npoints);
  win.ys = malloc (sizeof win.ys * win.npoints);
  for (size_t i = 0; i != win.npoints; ++i)
    {
      win.xs[i] = xs[i];
      win.ys[i] = ys[i];
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
