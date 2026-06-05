cmake_minimum_required(VERSION 3.16)
project(DawudEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(DawudEngine main.cpp
        game.cpp
        game.h
        ResourceHolder.h
        ResourceHolder.inl
        SceneNode.cpp
        SceneNode.h
        SpriteNode.cpp
        SpriteNode.h
        Aircraft.cpp
        Aircraft.h
        Entity.cpp
        Entity.h
        ResourceIndentifiers.h
        World.cpp
        World.h
)

target_link_libraries(DawudEngine sfml-graphics sfml-window sfml-system)
