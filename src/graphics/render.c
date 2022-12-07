#include "graphics/render.h"

#include <stdio.h>
#include <string.h>

#include "graphics/math.h"

#include "glad/glad.h"

static int    _initialized = 0;

static GLuint _VAO, _VBO;
static GLuint _shader_program = 0;

static mat4_t _projection = { 0.0f };

static char *_vertex_string =
    "#version 300 es\n"                                             \
    "layout(location = 0) in vec2 _pos;\n"                          \
    "uniform mat4 _proj;\n"                                         \
    "uniform mat4 _model;\n"                                        \
    "uniform vec4 _color;\n"                                        \
    "out vec4 color;\n"                                             \
    "void main()\n"                                                 \
    "{\n"                                                           \
    "   gl_Position = _proj * _model * vec4(_pos, 0.0f, 1.0f);\n"   \
    "   color = _color;\n"                                          \
    "}\n";

static char *_fragment_string =
    "#version 300 es\n"                                             \
    "precision mediump float;\n"                                    \
    "out vec4 fragColor;\n"                                         \
    "in vec4 color;\n"                                              \
    "void main()\n"                                                 \
    "{\n"                                                           \
    "   fragColor = color;\n"                                       \
    "}\n";

static int _render_check_shader(GLuint shader)
{
    char info_log[1024];
    int status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (!status) {
        glGetShaderInfoLog(shader, 1024, NULL, info_log);
        fprintf(stderr, "%s\n", info_log);
    }

    return status;
}

static int _render_init_shader(void)
{
    GLuint vertex_shader, fragment_shader;
    
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1,
                   (const char**) &_vertex_string,
                   NULL);

    glCompileShader(vertex_shader);

    if (!_render_check_shader(vertex_shader)) {
        return 0;
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1,
                   (const char**) &_fragment_string,
                   NULL);
    
    glCompileShader(fragment_shader);

    if (!_render_check_shader(fragment_shader)) {
        return 0;
    }

    _shader_program = glCreateProgram();
    glAttachShader(_shader_program, fragment_shader);
    glAttachShader(_shader_program, vertex_shader);
    glLinkProgram(_shader_program);

    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);
    return 1;
}

int render_init(proc_adr_fn proc_fn)
{
    int status = 1;

    static const GLfloat vertices[] = {
        0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
    };

    if (!(gladLoadGLLoader(proc_fn) && _render_init_shader())) {
        return 0;
    }

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                          2 * sizeof(GLfloat), NULL);
    
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return (_initialized = 1);
}

void render_viewport(int width, int height)
{
    if (!_initialized) return;

    math_to_unit_mtrx(_projection);

    _projection[0][0] = 2.0f / width;
    _projection[1][1] = 2.0f / -height;
    _projection[2][2] = -1.0f;

    _projection[3][0] = -1.0f;
    _projection[3][1] = 1.0f;

    render_gl_viewport(width, height);
}

void render_gl_viewport(int width, int height)
{
    glViewport(0, 0, width, height);
}

void render_clear(color_t color)
{
    if (!_initialized) return;

    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void render_rect(color_t color, float x, float y, float sx, float sy)
{
    float model_mtrx[4][4] = {0.0f};
    GLuint proj, model, _color;

    if (!_initialized) return;

    math_to_unit_mtrx(model_mtrx);
    math_scale_mtrx(model_mtrx, sx, sy);
    math_translate_mtrx(model_mtrx, x, y);

    proj = glGetUniformLocation(_shader_program, "_proj");
    glUniformMatrix4fv(proj, 1, GL_FALSE, (float*)_projection);

    model = glGetUniformLocation(_shader_program, "_model");
    glUniformMatrix4fv(model, 1, GL_FALSE, (float*)model_mtrx);

    _color = glGetUniformLocation(_shader_program, "_color");
    glUniform4f(_color, color.r, color.g, color.b, color.a);

    glUseProgram(_shader_program);
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}