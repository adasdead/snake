#ifndef GRAPHICS_MATH_H
#define GRAPHICS_MATH_H

#define math_to_unit_mtrx(mat)              \
    do {                                    \
        for (int i = 0; i < 4; i++) {       \
            mat[i][i] = 1.0f;               \
        }                                   \
    } while (0)

typedef struct {
    float x, y;
} vec2_t;

typedef float mat4_t[4][4];

void math_mult_mtrx(mat4_t dest, mat4_t src);
void math_scale_mtrx(mat4_t mat, float width, float height);
void math_translate_mtrx(mat4_t mat, float x, float y);

#endif /* GRAPHICS_MATH_H */