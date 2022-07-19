#ifndef GAME_SNAKE_H
#define GAME_SNAKE_H

#include <stdlib.h>

#include "graphics/graphics.h"

typedef enum
{
    SNAKE_DIR_UP,
    SNAKE_DIR_DOWN,
    SNAKE_DIR_LEFT,
    SNAKE_DIR_RIGHT,

} snake_direction_t;

typedef vec2f_t *snake_part_t;

typedef struct _snake_t
{
    snake_direction_t direction;
    snake_part_t *body;
    size_t body_size;

    snake_part_t removed_part;

    int alive;

} *snake_t;

snake_t new_snake(void);

void snake_draw(snake_t snake);

void snake_reset(snake_t snake);

void snake_move_forward(snake_t snake, snake_direction_t dir);

int snake_is_overlap(snake_t snake, vec2f_t pos);

void snake_restore_rm_part(snake_t snake);

void snake_destroy(snake_t snake);

#endif /* GAME_SNAKE_H */