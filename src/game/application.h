#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "graphics/graphics.h"

#include "definitions.h"

void application_init(void);

void application_loop(float delta);
void application_on_key(int key);

void application_free(void);

#endif /* GAME_APPLICATION_H */