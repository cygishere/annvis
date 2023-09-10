#include "window.h"

int
main (void)
{
  /* HACK: now setting width == height to make sure axis ratio is 1:1 */
  window_init (600, 600, "Annvis");

  window_run ();
  window_quit ();
}
