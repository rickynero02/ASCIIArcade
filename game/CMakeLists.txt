
add_library(game menu.cpp game.cpp)
add_dependencies(game maps)
add_dependencies(game entities)

target_link_libraries(game ${CURSES_LIBRARIES})
target_link_libraries(game entities)
target_link_libraries(game maps)