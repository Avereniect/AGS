cmake_minimum_required(VERSION 3.14)

add_library(AGS_image STATIC
    include/ags/image/Image.hpp
    include/ags/image/Pixel_buffer.hpp
    include/ags/image/Canvas.hpp

    src/Image.cpp

    include/ags/image/IO.hpp
    src/IO.cpp
)

target_link_libraries(AGS_image
    PRIVATE AUL AGS_core png
)

target_compile_features(AGS_image
    PUBLIC cxx_std_17
)

target_compile_definitions(AGS_image
    PRIVATE AGS_MODULE_NAME=AGS_IMAGE
)

target_include_directories(AGS_image PUBLIC ./include/)

add_subdirectory(./tests/)
