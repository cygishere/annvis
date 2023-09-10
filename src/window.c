#include "window.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

static struct Window_t
{
  u32 width;
  u32 height;
} window;

void
window_init (u32 width, u32 height, const char *name)
{
  window.width = width;
  window.height = height;

  SetConfigFlags (FLAG_MSAA_4X_HINT);
  InitWindow (width, height, name);
}

void
window_quit (void)
{
  CloseWindow ();
}

void
window_run (void)
{
  SetTargetFPS (60);
  while (!WindowShouldClose ())
    {
      /* handle events */
      if (IsKeyDown (KEY_LEFT_CONTROL))
        {
        }

      /* drawing */
      BeginDrawing ();
      ClearBackground (RAYWHITE);
      DrawText (
          "USE MOUSE LEFT-RIGHT CLICK to DEFINE LINE START and END POINTS", 15,
          20, 20, GRAY);

      // DrawLineBezier(start, end, 2.0f, RED);

      // DrawLineEx (start, startControl, 1.0, LIGHTGRAY);
      // DrawLineEx (end, endControl, 1.0, LIGHTGRAY);
      // DrawCircleV (startControl, 10, RED);
      // DrawCircleV (endControl, 10, RED);

      EndDrawing ();
    }
}
