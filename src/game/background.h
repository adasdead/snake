#ifndef GAME_BACKGROUND_H
#define GAME_BACKGROUND_H

#include "graphics/graphics.h"

static color_t _bg_color_1 = color_hex(0xf5f5f5);
static color_t _bg_color_2 = color_hex(0xeeeeee);
static color_t _border_clr = color_hex(0xe0e0e0);

static void background_draw(void)
{
    render_clear(_bg_color_1);

    for (int i = 0; i < FIELD_WIDTH; i++) {
        for (int j = 0; j < FIELD_HEIGHT; j++) {
            if ((i + j) & 1) {
                render_rect(_bg_color_2, i, j, 1, 1);
            }
        }
    }

    render_rect(_border_clr, 0, 0, FIELD_WIDTH, 1);
    render_rect(_border_clr, 0, FIELD_HEIGHT - 1, FIELD_WIDTH, 1);
    render_rect(_border_clr, 0, 0, 1, FIELD_HEIGHT);
    render_rect(_border_clr, FIELD_WIDTH - 1, 0, 1, FIELD_HEIGHT);
}

#endif /* GAME_BACKGROUND_H */