cmake_minimum_required(VERSION 3.16)

add_library(AGS_ui STATIC
    src/Window.hpp
    src/Window.cpp
)

target_link_libraries(AGS_ui
    PUBLIC AGS_core AGS_ARE glfw
)

target_compile_definitions(AGS_ui
    PRIVATE AGS_MODULE_NAME="AGS_ui"
)

target_include_directories(AGS_ui PUBLIC ./include/)
