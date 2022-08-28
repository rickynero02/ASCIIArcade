

add_library(maps map.cpp)
target_link_libraries(maps ${CURSES_LIBRARIES})
target_link_libraries(maps entities)