add_library(cursesui STATIC
    cursesui.cpp
)

target_link_libraries(cursesui PUBLIC
    mycurses
    snake
)

target_include_directories(cursesui INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}"
)

