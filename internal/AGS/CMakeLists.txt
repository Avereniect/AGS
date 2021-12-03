cmake_minimum_required(VERSION 3.16)

add_executable(AGS
    src/AGS_main.cpp
)

target_compile_features(AGS PRIVATE cxx_std_17)

target_link_libraries(AGS PUBLIC AGS_core AUL AVML)

target_include_directories(AGS
    PUBLIC
    ../../internal/image/include/
)
