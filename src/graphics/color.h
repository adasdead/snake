#ifndef GRAPHICS_COLOR_H
#define GRAPHICS_COLOR_H

#include <stdint.h>

typedef struct
{
    float r, g, b, a;

} color_t;

color_t new_color_f(float r, float g, float b, float a);
color_t new_color_i(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
color_t new_color_hex(const char *hex);

#endif /* GRAPHICS_COLOR_H */