cmake_minimum_required(VERSION 3.0.0)
project(ASCIIArcade VERSION 0.1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_subdirectory(entities)
add_subdirectory(maps)
add_subdirectory(game)

add_executable(ASCIIArcade main.cpp)
target_link_libraries(ASCIIArcade ${CURSES_LIBRARIES})

target_link_libraries(ASCIIArcade entities)
add_dependencies(ASCIIArcade entities)

target_link_libraries(ASCIIArcade maps)
add_dependencies(ASCIIArcade maps)

target_link_libraries(ASCIIArcade game)
add_dependencies(ASCIIArcade game)


