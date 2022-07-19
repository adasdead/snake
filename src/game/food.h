#ifndef GAME_FOOD_H
#define GAME_FOOD_H

#include <stdlib.h>

#include "graphics/graphics.h"

#include "game/snake.h"

typedef vec2f_t food_t;

static float             _food_anim_timer = 0.0f;

static void food_move_random(food_t *food, snake_t snake)
{
    food->x = (rand() % (FIELD_WIDTH - 2)) + 1;
    food->y = (rand() % (FIELD_HEIGHT - 2)) + 1;

    if (snake_is_overlap(snake, *food))
        food_move_random(food, snake);
}

static void food_draw(food_t *food, float delta)
{
    color_t food_color = new_color_hex("#ffa726");

    if (_food_anim_timer < 0.6)
        render_rect(food_color, food->x, food->y, 1, 1);
    else
    {
        if (_food_anim_timer > 1)
            _food_anim_timer = 0.0f;

        render_rect(food_color, food->x + 0.25f,
                    food->y + 0.25f, 0.5f, 0.5f);
    }

    _food_anim_timer += delta;
}

#endif /* GAME_FOOD_H */