#include "game/application.h"

#include "game/background.h"

#include "game/snake.h"
#include "game/food.h"

static snake_t            _snake;
static food_t             _snake_food;

static float              _snake_move_timer = 0.0f;
static snake_direction_t  _snake_cur_dir;


void application_init(void)
{
    _snake = new_snake();
    _snake_cur_dir = SNAKE_DIR_RIGHT;
    
    food_move_random(&_snake_food, _snake);
}

void application_loop(float delta)
{
    background_draw();
    food_draw(&_snake_food, delta);
    snake_draw(_snake);
    
    if (_snake_move_timer > SNAKE_MOVE_PERIOD)
    {
        snake_move_forward(_snake, _snake_cur_dir);

        if (snake_is_overlap(_snake, _snake_food))
        {
            food_move_random(&_snake_food, _snake);
            snake_restore_rm_part(_snake);
        }

        if (!_snake->alive)
        {
            _snake_cur_dir = SNAKE_DIR_RIGHT;
            
            snake_reset(_snake);
        }

        _snake_move_timer = 0.0f;
    }

    _snake_move_timer += delta;
}

void application_on_key(int key)
{
    switch (key)
    {
    case GLFW_KEY_W:
    case GLFW_KEY_UP:
        _snake_cur_dir = SNAKE_DIR_UP;
        break;
    
    case GLFW_KEY_A:
    case GLFW_KEY_LEFT:
        _snake_cur_dir = SNAKE_DIR_LEFT;
        break;

    case GLFW_KEY_S:
    case GLFW_KEY_DOWN:
        _snake_cur_dir = SNAKE_DIR_DOWN;
        break;

    case GLFW_KEY_D:
    case GLFW_KEY_RIGHT:
        _snake_cur_dir = SNAKE_DIR_RIGHT;
        break;
    }
}

void application_free(void)
{
    snake_destroy(_snake);
}