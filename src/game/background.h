#ifndef GAME_BACKGROUND_H
#define GAME_BACKGROUND_H

#include "graphics/graphics.h"

static void background_draw(void)
{
    color_t bg_color_1 = new_color_hex("#f5f5f5");
    color_t bg_color_2 = new_color_hex("#eeeeee");
    color_t border_clr = new_color_hex("#e0e0e0");

    render_clear(bg_color_1);

    for (int i = 0; i < FIELD_WIDTH; i++)
    {
        for (int j = 0; j < FIELD_HEIGHT; j++)
        {
            if (((i + j) % 2) == 0)
                render_rect(bg_color_2, i, j, 1, 1);
        }
    }

    render_rect(border_clr, 0, 0, FIELD_WIDTH, 1);
    render_rect(border_clr, 0, FIELD_HEIGHT - 1, FIELD_WIDTH, 1);
    render_rect(border_clr, 0, 0, 1, FIELD_HEIGHT);
    render_rect(border_clr, FIELD_WIDTH - 1, 0, 1, FIELD_HEIGHT);
}

#endif /* GAME_BACKGROUND_H */