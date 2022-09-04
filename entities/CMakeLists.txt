

add_library(entities player.cpp bullet.cpp state.cpp artifact.cpp enemy.cpp entity.cpp)
target_link_libraries(entities ${CURSES_LIBRARIES})