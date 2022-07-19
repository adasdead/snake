#include "snake.h"

#include <string.h>

#include "definitions.h"

static void snake_add_back_part(snake_t snake, vec2f_t pos)
{
    size_t new_size = sizeof(snake_part_t) * snake->body_size;

    snake->body = realloc(snake->body, new_size + sizeof(snake_part_t));

    memmove(snake->body + 1, snake->body, new_size);

    snake->body[0] = malloc(sizeof(vec2f_t));
    memcpy(snake->body[0], &pos, sizeof(vec2f_t));

    snake->body_size++;
}

static void snake_add_front_part(snake_t snake, vec2f_t pos)
{
    size_t new_size = sizeof(snake_part_t) * (snake->body_size + 1);

    snake->body = realloc(snake->body, new_size);

    snake->body[snake->body_size] = malloc(sizeof(vec2f_t));
    memcpy(snake->body[snake->body_size], &pos, sizeof(vec2f_t));

    snake->body_size++;
}

static snake_part_t snake_remove_back_part(snake_t snake)
{
    snake_part_t returned_part = snake->body[0];
    size_t new_size = sizeof(snake_part_t) * (snake->body_size - 1);

    memmove(snake->body, snake->body + 1, new_size);

    snake->body = realloc(snake->body, new_size);

    snake->body_size--;

    return returned_part;
}

static snake_direction_t snake_dir_opposite(snake_direction_t dir)
{
    switch (dir)
    {
    case SNAKE_DIR_UP:    return SNAKE_DIR_DOWN;
    case SNAKE_DIR_DOWN:  return SNAKE_DIR_UP;
    case SNAKE_DIR_LEFT:  return SNAKE_DIR_RIGHT;
    case SNAKE_DIR_RIGHT: return SNAKE_DIR_LEFT;
    }

    return dir;
}

snake_t new_snake(void)
{
    snake_t _snake = malloc(sizeof(struct _snake_t));
    _snake->body_size = 0;
    _snake->body = NULL;

    snake_reset(_snake);

    return _snake;
}

void snake_draw(snake_t snake)
{
    color_t snake_color_1 = new_color_hex("#7cb342");
    color_t snake_color_2 = new_color_hex("#689f38");

    for (int i = 0; i < snake->body_size; i++)
    {
        color_t color;
        snake_part_t part = snake->body[i];

        if ((i % 2) == 0)
            color = snake_color_1;
        else
            color = snake_color_2;

        render_rect(color, part->x, part->y, 1, 1);  
    }
}

void snake_reset(snake_t snake)
{
    if (snake->body_size > 0)
    {
        for (int i = 0; i < snake->body_size; i++)
            free(snake->body[i]);

        free(snake->body);

        snake->body_size = 0;
        snake->body = NULL;
    }

    for (int i = 0; i < SNAKE_START_SIZE; i++)
    {
        snake_add_front_part(snake, (vec2f_t)
        {
            SNAKE_START_X + i,
            SNAKE_START_Y
        });   
    }

    snake->direction = SNAKE_DIR_RIGHT;
    snake->removed_part = NULL;
}

void snake_move_forward(snake_t snake,
                        snake_direction_t dir)
{
    vec2f_t new_pos = *snake->body[snake->body_size - 1];

    if (dir != -1)
    {
        if (snake_dir_opposite(snake->direction) != dir)
            snake->direction = dir;
    }

    switch (snake->direction)
    {
    case SNAKE_DIR_UP:    new_pos.y--; break;
    case SNAKE_DIR_DOWN:  new_pos.y++; break;
    case SNAKE_DIR_LEFT:  new_pos.x--; break;
    case SNAKE_DIR_RIGHT: new_pos.x++; break;
    }

    if (snake_is_overlap(snake, new_pos))
        snake->alive = 0;
    else
    {
        snake->alive = 
            (new_pos.x > 0) && (new_pos.y > 0) &&
            (new_pos.x < FIELD_WIDTH  - 1) &&
            (new_pos.y < FIELD_HEIGHT - 1);
    }

    snake->removed_part = snake_remove_back_part(snake);
    snake_add_front_part(snake, new_pos);
}

int snake_is_overlap(snake_t snake, vec2f_t pos)
{
    size_t checked = 0;

    for (int i = 0; i < snake->body_size; i++)
    {
        if (pos.x == snake->body[i]->x &&
            pos.y == snake->body[i]->y)
        {
            return 1;
        }

        if ((++checked) == snake->body_size)
            break;
    }

    return 0;
}

void snake_restore_rm_part(snake_t snake)
{
    snake_add_back_part(snake, *snake->removed_part);
}

void snake_destroy(snake_t snake)
{
    for (int i = 0; i < snake->body_size; i++)
        free(snake->body[i]);

    free(snake->body);
    free(snake);
}