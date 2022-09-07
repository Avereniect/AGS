cmake_minimum_required(VERSION 3.16)

set(APT_BUILD_TESTS on)

option(APT_BUILD_TESTS off)

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

    src/Window_functions.hpp
    src/Window_functions.cpp

    src/LBVH.hpp
    src/LBVH.cpp
)

target_compile_features(APT PUBLIC cxx_std_17)

target_link_libraries(APT
    PUBLIC AGS_image AVEL AVML AUL
)

target_compile_options(APT PUBLIC "-march=native")
target_link_options(APT PRIVATE)

target_include_directories(APT PUBLIC ./include/)

if (APT_BUILD_TESTS)
    add_subdirectory(tests/)
endif()
