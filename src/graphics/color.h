#ifndef GRAPHICS_COLOR_H
#define GRAPHICS_COLOR_H

typedef struct {
    float r, g, b, a;
} color_t;

#define color_f(r, g, b, a) ((color_t) { r, g, b, a })
#define color_i(r, g, b, a)                                         \
    color_f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f)

#define color_hex(hex)                                              \
    color_i(((hex & 0xff0000) >> 16), ((hex & 0x00ff00) >> 8),      \
            (hex & 0x0000ff), 255)

#endif /* GRAPHICS_COLOR_H */