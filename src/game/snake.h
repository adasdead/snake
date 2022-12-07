#ifndef GAME_SNAKE_H
#define GAME_SNAKE_H

#include <stdlib.h>

#include "graphics/graphics.h"

typedef struct snake_part
{
    vec2_t pos;
    struct snake_part *next;
    struct snake_part *prev;
} snake_part_t;

typedef enum {
    SNAKE_DIR_UP,
    SNAKE_DIR_DOWN,
    SNAKE_DIR_LEFT,
    SNAKE_DIR_RIGHT,
} snake_direction_t;

typedef struct {
    snake_direction_t direction;
    snake_part_t *removed_part;
    snake_part_t *head, *tail;
    unsigned int is_alive;
    size_t size;
} snake_t;

snake_t *snake_new(void);

void snake_draw(const snake_t *snake);

void snake_reset(snake_t *snake);

void snake_move_forward(snake_t *snake, snake_direction_t dir);

int snake_is_overlap(const snake_t *snake, const vec2_t *pos);

void snake_restore_part(snake_t *snake);

void snake_destroy(snake_t *snake);

#endif /* GAME_SNAKE_H */