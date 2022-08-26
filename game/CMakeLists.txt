
add_library(game menu.cpp game.cpp)
target_link_libraries(game ${CURSES_LIBRARIES})
target_link_libraries(game maps)