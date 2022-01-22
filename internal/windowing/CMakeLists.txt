cmake_minimum_required(VERSION 3.16)

add_library(AGS_windowing STATIC
    ../ui/src/Window.cpp
    src/Windowing_context.cpp
)

target_link_libraries(AGS_windowing PUBLIC AGS_core glfw glad)
target_include_directories(AGS_windowing PUBLIC ./include/)
