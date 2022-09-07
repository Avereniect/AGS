cmake_minimum_required(VERSION 3.16)

set(context_source_files)

add_library(AGS_core STATIC
    src/Types.cpp

    src/Windowing_context.hpp
    src/Windowing_context.cpp
    src/Util.cpp

    include/ags/Graphics_includes.hpp
    include/ags/Logging.hpp
    include/ags/Types.hpp
    include/ags/Util.hpp
)

target_compile_features(AGS_core PUBLIC cxx_std_17)

if(AGS_USE_OPENGL)
    set(AGS_GRAPHICS_LIBRARIES glad GL)
    target_compile_definitions(AGS_core PUBLIC AGS_OPENGL)
endif()

if (AGS_USE_VULKAN)
    set(AGS_GRAPHICS_LIBRARIES vulkan)
    target_compile_definitions(AGS_core PUBLIC AGS_VULKAN)
endif()

target_link_libraries(AGS_core PUBLIC AUL AVML spdlog glfw ${AGS_GRAPHICS_LIBRARIES})

target_compile_definitions(AGS_core
    PRIVATE AGS_MODULE_NAME=AGS_core
)

target_include_directories(AGS_core
    PUBLIC
    ../../external/half-2.2.0/include/
    ./include/
)
