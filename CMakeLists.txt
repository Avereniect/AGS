cmake_minimum_required(VERSION 3.16)

project(AGS
    VERSION 1.0.0
    DESCRIPTION "A graphics sandbox"
    LANGUAGES CXX
)

add_subdirectory(external/AUL/)
add_subdirectory(external/AVML/)

add_subdirectory(internal/AGS/)
add_subdirectory(internal/AGS_core/)
add_subdirectory(internal/image/)
