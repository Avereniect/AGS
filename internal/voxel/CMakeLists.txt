cmake_minimum_required(VERSION 3.16)

add_library(AGS_voxel STATIC
    src/VOX_chunked_volume.hpp
    src/VOX_chunked_volume.cpp

    include/ags/voxel/Voxel_canvas.hpp
    src/Voxel_canvas.cpp
)

target_compile_features(AGS_voxel PUBLIC cxx_std_17)

target_include_directories(AGS_voxel PUBLIC ./include/)
