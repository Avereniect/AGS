cmake_minimum_required(VERSION 3.14)

add_library(APT STATIC
    src/Common.hpp
    src/Render_settings.hpp
    src/Camera.hpp
    src/Scene.hpp
)

target_link_libraries(APT
    PUBLIC
    AGS_image

    PRIVATE
    AUL
    AVEL
    AVML
)

target_include_directories(APT PUBLIC ./include/)
