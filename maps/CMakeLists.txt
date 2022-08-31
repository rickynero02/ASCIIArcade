
add_library(maps map.cpp info.cpp)
target_link_libraries(maps ${CURSES_LIBRARIES})
add_dependencies(maps entities)
target_link_libraries(maps entities)