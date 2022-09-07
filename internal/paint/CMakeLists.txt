cmake_minimum_required(VERSION 3.16)

add_library(AGS_paint STATIC
    src/Common.hpp

    src/tile_identification/Tile_identifier.hpp
    src/tile_identification/Tile_identifier.cpp
)

target_link_libraries(AGS_paint
    PRIVATE AUL AGS_core AGS_image
)

target_compile_features(AGS_paint
    PUBLIC cxx_std_17
)

target_compile_definitions(AGS_paint
    PRIVATE AGS_MODULE_NAME=AGS_PAINT
)

target_include_directories(AGS_paint PUBLIC ./include/)
