cmake_minimum_required(VERSION 3.14)

add_library(AGS_image STATIC
    include/ags/image/IMG_image.hpp
    include/ags/image/IMG_pixel_buffer.hpp
    include/ags/image/IMG_canvas.hpp
    src/IMG_image.cpp
)

target_include_directories(AGS_image PUBLIC ./include/)
