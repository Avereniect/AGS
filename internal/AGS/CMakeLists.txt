cmake_minimum_required(VERSION 3.16)

add_executable(AGS
    src/Main.cpp

    src/Engine.hpp
    src/Engine.cpp
)


add_custom_target(LINK_ASSETS
    COMMAND cmake -E create_symlink "${PROJECT_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/assets"
)


target_compile_features(AGS PRIVATE cxx_std_17)

target_link_libraries(AGS PUBLIC AGS_core AGS_ARE AGS_ui AUL AVML AVEL)

target_compile_options(AGS PRIVATE "-march=native")
add_dependencies(AGS LINK_ASSETS)
