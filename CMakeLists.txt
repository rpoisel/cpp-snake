cmake_minimum_required(VERSION 3.5)
project(CPP-SNAKE)

add_subdirectory(game)
add_subdirectory(snake)
add_subdirectory(mycurses)
add_subdirectory(cursesui)

add_executable(main
    main.cpp
)

target_link_libraries(main
    cursesui
    snake
)
