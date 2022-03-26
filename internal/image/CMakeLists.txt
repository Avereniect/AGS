cmake_minimum_required(VERSION 3.14)

add_library(AGS_image STATIC
    include/ags/image/Image.hpp
    include/ags/image/Pixel_buffer.hpp
    include/ags/image/Canvas.hpp
    src/Image.cpp
)

target_include_directories(AGS_image PUBLIC ./include/)
