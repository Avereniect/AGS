cmake_minimum_required(VERSION 3.16)

add_library(AGS_core STATIC
    src/AGS_types.cpp
)

target_compile_features(AGS_core PRIVATE cxx_std_17)

target_link_libraries(AGS_core AUL AVML)

target_include_directories(AGS_core
    PUBLIC
    ../../external/half-2.2.0/include/
    ./include/
)