cmake_minimum_required(VERSION 3.16)

add_library(AGS_mesh STATIC
    src/
)

target_link_libraries(AGS_mesh PUBLIC AGS_core)
target_include_directories(AGS_mesh PUBLIC ./include/)
