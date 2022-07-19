#ifndef GRAPHICS_RENDER_H
#define GRAPHICS_RENDER_H

#include "graphics/color.h"

typedef void*(*proc_adr_fn)(const char*);

int render_init(proc_adr_fn proc_fn);

void render_viewport(int width, int height);
void render_gl_viewport(int width, int height);

void render_clear(color_t color);

void render_rect(color_t color, float x, float y,
                 float sx, float sy);

#endif /* GRAPHICS_RENDER_H */