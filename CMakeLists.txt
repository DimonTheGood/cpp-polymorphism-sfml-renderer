cmake_minimum_required(VERSION 3.15)
project(figure_render VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

set(SOURCES
    main.cpp
)

add_executable(figure_render ${SOURCES})

target_link_libraries(figure_render
    sfml-graphics
    sfml-window
    sfml-system
)