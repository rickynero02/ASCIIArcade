

add_library(maps map.cpp state.cpp)
target_link_libraries(maps ${CURSES_LIBRARIES})
target_link_libraries(maps entities)