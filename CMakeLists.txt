cmake_minimum_required(VERSION 3.14)
project(PlatformerSFML)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
    find_package(SFML 2.6 REQUIRED COMPONENTS
    graphics
    window
    system
    network
    audio
)
endif()


find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h
        src/Vector2.cpp
        src/Vector2.h
        src/GameObject.cpp
        src/GameObject.h
        src/TileMap.cpp
        src/TileMap.h
        src/Entity.cpp
        src/Entity.h
        src/Entity.h
        src/Entity.cpp
        src/Entity.h
        src/Entity.cpp
        src/Player.cpp
        src/Player.h
        src/Enemy.cpp
        src/Enemy.h)
add_executable(PlatformerSFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (PlatformerSFML sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)