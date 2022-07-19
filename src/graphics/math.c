#include "math.h"

#include <string.h>

void math_to_unit_mtrx(mat4_t m)
{
    for (int i = 0; i < 4; i++)
        m[i][i] = 1.0f;
}

void math_mult_mtrx(mat4_t dest, mat4_t src)
{
    float mult[4][4] = {0.0f};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
                mult[i][j] += dest[i][k] * src[k][j];
        }
    }

    memcpy(dest, mult, sizeof(mult));
}

void math_scale_mtrx(mat4_t m, float width, float height)
{
    float scale[4][4] = {0.0f};

    math_to_unit_mtrx(scale);

    scale[0][0] *= width;
    scale[1][1] *= height;
    scale[1][2] *= 1.0f;

    math_mult_mtrx(m, scale);
}

void math_translate_mtrx(mat4_t m, float x, float y)
{
    float trans[4][4] = {0.0f};

    math_to_unit_mtrx(trans);

    trans[3][0] = x;
    trans[3][1] = y;
    trans[3][2] = 1.0f;

    math_mult_mtrx(m, trans);
}