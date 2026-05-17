cmake_minimum_required(VERSION 3.16)
project(DawudEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(DawudEngine main.cpp
        game.cpp
        game.h)

target_link_libraries(DawudEngine sfml-graphics sfml-window sfml-system)

# Copy Media folder to build directory
add_custom_command(TARGET DawudEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Media
        ${CMAKE_BINARY_DIR}/Media
    COMMENT "Copying Media folder to build directory"
)

