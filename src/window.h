#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <stdint.h>

typedef uint32_t u32;

void window_init (u32 width, u32 height, const char *name);
void window_quit (void);

void window_run (void);
int window_is_point_in_bounds (u32 point_id);

#endif /* _WINDOW_H_ */
