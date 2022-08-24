
add_library(entities player.cpp entity.cpp)
target_link_libraries(entities ${CURSES_LIBRARIES})