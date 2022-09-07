cmake_minimum_required(VERSION 3.16)

add_executable(AGS
    src/Main.cpp

    src/Engine.hpp
    src/Engine.cpp
)



# This target is used to create a symbolic link from the location of the
# generated executable to the assets folder so that the
add_custom_target(LINK_ASSETS
    COMMAND cmake -E create_symlink "${PROJECT_SOURCE_DIR}/assets" "${CMAKE_CURRENT_BINARY_DIR}/assets"
)

add_dependencies(AGS LINK_ASSETS)



target_compile_features(AGS PUBLIC cxx_std_17)

target_link_libraries(AGS
    PUBLIC APT AGS_core AGS_ARE AGS_ui AUL AVML AVEL AGS_threading AGS_image STB
)

target_compile_options(AGS PRIVATE "-march=native") # "-fsanitize=address")
target_link_options(AGS PRIVATE ) #"-fsanitize=address")

if (ipo_supported AND ${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set_target_properties(AGS PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
    target_compile_options(AGS PRIVATE "-flto=auto")
endif()
