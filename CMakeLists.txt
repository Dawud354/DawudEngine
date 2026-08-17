cmake_minimum_required(VERSION 3.16)
project(DawudEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# AI said to do this cos writing include src is bad
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(DawudEngine ${SOURCES})

# since i moved them around i need to add all the sub folders
target_include_directories(DawudEngine PRIVATE include
        include/DawudEngine
        include/DawudEngine/Core
        include/DawudEngine/Scene
        include/DawudEngine/Graphics
)

target_link_libraries(DawudEngine sfml-graphics sfml-window sfml-system)
