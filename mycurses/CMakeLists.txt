add_library(mycurses STATIC
    mycurses.cpp
)

target_link_libraries(mycurses PUBLIC
    ncurses
)

target_include_directories(mycurses PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}"
)
