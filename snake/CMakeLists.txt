add_library(snake STATIC
    characters.cpp
    states.cpp
)

target_link_libraries(snake PUBLIC
    game
)

target_include_directories(snake INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}"
)
