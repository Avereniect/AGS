cmake_minimum_required(VERSION 3.14)

add_library(APT STATIC
    src/Common.hpp

    src/Render_settings.hpp

    src/Camera.hpp

    src/scene/Scene.cpp
    src/scene/Scene.hpp

    src/Render.hpp
    src/Render.cpp

    src/Intersection.hpp
    src/Intersection.cpp

    src/Random.hpp
    src/Random.cpp
)

target_link_libraries(APT
    PUBLIC AGS_image
    PRIVATE AUL AVEL AVML
)

target_compile_options(APT PRIVATE "-march=native")
target_link_options(APT PRIVATE)

target_include_directories(APT PUBLIC ./include/)
