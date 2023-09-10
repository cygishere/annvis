#include "window.h"

int
main (void)
{
  window_init (800, 600, "Annvis");

  window_run ();
  window_quit ();
}
