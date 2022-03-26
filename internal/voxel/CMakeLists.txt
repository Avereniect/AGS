cmake_minimum_required(VERSION 3.16)

add_library(AGS_voxel STATIC
    src/VOX_chunked_volume.hpp
    src/VOX_chunked_volume.cpp
)

target_include_directories(AGS_voxel PUBLIC ./include/)
