#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game/application.h"

static float        _last_time;
static GLFWwindow  *_window;

static void _key_callback(GLFWwindow* window, int key, int scancode,
                          int action, int mods)
{
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        application_on_key(key);
    }
}

int main(void)
{
    float current_time, delta_time;
    int width, height;

    srand(time(NULL));

    if (!glfwInit()) {
        fprintf(stderr, "GLFW initialization error!");
        return -1;
    }
 
    _window = glfwCreateWindow(FIELD_WIDTH * WINDOW_SIZE_FACTOR_PX, 
                               FIELD_HEIGHT * WINDOW_SIZE_FACTOR_PX,
                               APPLICATION_NAME, NULL, NULL);

    if (!_window)
    {
        fprintf(stderr, "Window creating error!");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(_window);
    glfwSetKeyCallback(_window, _key_callback);
    glfwSwapInterval(1);

    if (!render_init((proc_adr_fn)glfwGetProcAddress)) {
        fprintf(stderr, "OpenGL initialization error!");
        glfwDestroyWindow(_window);
        glfwTerminate();
        return 0;
    }

    application_init();

    render_viewport(FIELD_WIDTH, FIELD_HEIGHT);

    while (!glfwWindowShouldClose(_window)) {
        current_time = (float) glfwGetTime();
        delta_time = current_time - _last_time;
        _last_time = current_time;

        glfwGetFramebufferSize(_window, &width, &height);
        render_gl_viewport(width, height);

        application_loop(delta_time);

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }

    application_free();
    
    glfwDestroyWindow(_window);
    glfwTerminate();
    return 0;
}