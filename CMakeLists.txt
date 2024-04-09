cmake_minimum_required(VERSION 3.5.0)
project(snake-the-game VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sfml/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(LOAD_TEXTURES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/LoadTextures")
set(LOAD_SPRITES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Sprites")

add_executable(snake-the-game snake-the-game.cpp)

target_link_libraries(snake-the-game sfml-graphics sfml-window sfml-system sfml-audio)

include_directories(${LOAD_TEXTURES_DIR})
include_directories(${LOAD_SPRITES_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
