#include "snake.h"

#include <string.h>

#include "definitions.h"

static color_t _snake_color_1 = color_hex(0x7cb342);
static color_t _snake_color_2 = color_hex(0x689f38);

static snake_direction_t _dir_opposite(snake_direction_t dir)
{
    switch (dir) {
    case SNAKE_DIR_UP:    return SNAKE_DIR_DOWN;
    case SNAKE_DIR_DOWN:  return SNAKE_DIR_UP;
    case SNAKE_DIR_LEFT:  return SNAKE_DIR_RIGHT;
    case SNAKE_DIR_RIGHT: return SNAKE_DIR_LEFT;
    }

    return dir;
}

static snake_part_t *_part_new(vec2_t pos)
{
    snake_part_t *tmp = malloc(sizeof *tmp);
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->pos = pos;
    return tmp;
}

static void _part_push_back(snake_t *snake, vec2_t pos)
{
    snake_part_t *part = _part_new(pos);

    if (snake->tail) {
        snake->tail->next = part;
        part->prev = snake->tail;
        snake->tail = part;
    }
    else {
        snake->tail = part;
        snake->head = part;
    }
}

static void _part_push_front(snake_t *snake, vec2_t pos)
{
    snake_part_t *part = _part_new(pos);

    if (snake->head) {
        snake->head->prev = part;
        part->next = snake->head;
        snake->head = part;
    }
    else {
        snake->tail = part;
        snake->head = part;
    }
}

static snake_part_t *_part_pop_back(snake_t *snake)
{
    snake_part_t *part = snake->tail;

    if (part) {
        snake->tail = part->prev;
        snake->tail->next = NULL;
        return part;
    }
    
    return NULL;
}

snake_t *snake_new(void)
{
    snake_t *_snake = malloc(sizeof *_snake);

    memset(_snake, 0, sizeof *_snake);
    snake_reset(_snake);
    return _snake;
}

void snake_draw(const snake_t *snake)
{
    int i = 0;
    snake_part_t *part = snake->head;
    color_t color;

    do {
        if (i++ & 1) {
            color = _snake_color_1;
        }
        else {
            color = _snake_color_2;
        }

        render_rect(color, part->pos.x, part->pos.y, 1, 1);  
        
    } while (part = part->next);
}

void snake_reset(snake_t *snake)
{
    int i;
    vec2_t start = { SNAKE_START_X, SNAKE_START_Y };
    snake_part_t *prev, *next = snake->head;

    while (prev = next) {
        next = next->next;
        free(prev);
        prev = NULL;
    }

    snake->head = snake->tail = NULL;
    
    for (i = 0; i < SNAKE_START_SIZE; i++) {
        _part_push_front(snake, start);
        start.x += 1;
    }

    snake->direction = SNAKE_DIR_RIGHT;
    snake->removed_part = NULL;
}

void snake_move_forward(snake_t *snake, snake_direction_t dir)
{
    vec2_t new_pos = snake->head->pos;

    if (dir != -1) {
        if (_dir_opposite(snake->direction) != dir) {
            snake->direction = dir;
        }
    }

    switch (snake->direction)
    {
    case SNAKE_DIR_UP:    new_pos.y--; break;
    case SNAKE_DIR_DOWN:  new_pos.y++; break;
    case SNAKE_DIR_LEFT:  new_pos.x--; break;
    case SNAKE_DIR_RIGHT: new_pos.x++; break;
    }

    if (snake_is_overlap(snake, &new_pos)) {
        snake->is_alive = 0;
    }
    else {
        snake->is_alive = (new_pos.x > 0) && (new_pos.y > 0) &&
                          (new_pos.x < FIELD_WIDTH  - 1)     &&
                          (new_pos.y < FIELD_HEIGHT - 1);
    }

    if (snake->removed_part) {
        free(snake->removed_part);
    }

    snake->removed_part = _part_pop_back(snake);

    _part_push_front(snake, new_pos);
}

int snake_is_overlap(const snake_t *snake, const vec2_t *pos)
{
    snake_part_t *prev, *next = snake->head;

    while (prev = next) {
        next = next->next;
        
        if (pos->x == prev->pos.x && pos->y == prev->pos.y) {
            return 1;
        }
    }

    return 0;
}

void snake_restore_part(snake_t *snake)
{
    _part_push_back(snake, snake->removed_part->pos);
}

void snake_destroy(snake_t *snake)
{
    snake_part_t *prev, *next = snake->head;

    while (prev = next) {
        next = next->next;
        free(prev);
        prev = NULL;
    }
    
    free(snake);
}