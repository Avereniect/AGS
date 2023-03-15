cmake_minimum_required(VERSION 3.16)

project(AGS
    VERSION 1.0.0
    DESCRIPTION "A graphics sandbox"
    LANGUAGES C CXX
)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)

find_program(ccache_found ccache)
if (ccache_found)
    set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif()


include("ags_module.cmake")


if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(AGS_DEBUG ON)
endif()



set(AGS_THREADING_BUILD_TESTS ON)

option(AGS_USE_VULKAN OFF)
option(AGS_USE_OPENGL OFF)

if(AGS_USE_VULKAN AND AGS_USE_OPENGL)
    message(FATAL_ERROR "No rendering API selected.")
endif()



if(AGS_USE_VULKAN)
    set(AGS_RENDER_API "vulkan")
    add_subdirectory(external/glslang/)
endif()

if(AGS_USE_OPENGL)
    set(AGS_RENDER_API "opengl")

    add_subdirectory(external/glad/)
endif()


add_subdirectory(external/stb/)
add_subdirectory(external/quill/)

# External libraries maintained by project author
add_subdirectory(external/AUL/)
add_subdirectory(external/AVML/)
add_subdirectory(external/AVEL/)

# Internal targets
add_subdirectory(internal/AGS/)
add_subdirectory(internal/AGS_core/)
add_subdirectory(internal/APT/)
add_subdirectory(internal/ARE/)
add_subdirectory(internal/image/)
add_subdirectory(internal/mesh/)
add_subdirectory(internal/paint/)
add_subdirectory(internal/scene/)
add_subdirectory(internal/threading/)
add_subdirectory(internal/ui/)
add_subdirectory(internal/voxel/)
