find_package(glfw3 REQUIRED)

add_executable(snake)

target_sources(snake PRIVATE
    main.c

    game/application.c
    game/snake.c

    graphics/color.c
    graphics/render.c
    graphics/math.c

    glad/glad.c
)

target_include_directories(snake PRIVATE
    .
)

target_link_libraries(snake PRIVATE
    glfw
)