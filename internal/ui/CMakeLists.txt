cmake_minimum_required(VERSION 3.16)

add_library(AGS_ui STATIC
    src/Window.hpp
    src/Window.cpp
)

target_link_libraries(AGS_ui PUBLIC AGS_core)
target_include_directories(AGS_ui PUBLIC ./include/)
