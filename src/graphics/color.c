#include "graphics/color.h"

#include <string.h>
#include <stdlib.h>

#define COLOR_HEX_LEN 6

color_t new_color_f(float r, float g, float b, float a)
{
    return (color_t) { r, g, b, a };
}

color_t new_color_i(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (color_t) { r / 255.f, g / 255.f, b / 255.f, a / 255.f };
}

color_t new_color_hex(const char *hex)
{
    char buffer[COLOR_HEX_LEN + 1];

    if (strlen(hex) < COLOR_HEX_LEN)
        return (color_t) {0.f};

    if (*hex == '#')
        strncpy(buffer, hex + 1, COLOR_HEX_LEN);
    else
        strncpy(buffer, hex, COLOR_HEX_LEN);

    int number = (int)strtol(buffer, NULL, 16);

    return new_color_i(
        (number & 0xff0000) >> 16,
        (number & 0x00ff00) >> 8,
        (number & 0x0000ff), 255
    );
}