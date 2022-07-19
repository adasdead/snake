#ifndef GRAPHICS_MATH_H
#define GRAPHICS_MATH_H

typedef struct
{
    float x, y;

} vec2f_t;

typedef float mat4_t[4][4];

void math_to_unit_mtrx(mat4_t m);

void math_mult_mtrx(mat4_t dest, mat4_t src);

void math_scale_mtrx(mat4_t m, float width, float height);

void math_translate_mtrx(mat4_t m, float x, float y);

#endif /* GRAPHICS_MATH_H */