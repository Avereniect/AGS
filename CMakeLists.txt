cmake_minimum_required(VERSION 3.16)

project(AGS
    VERSION 1.0.0
    DESCRIPTION "A graphics sandbox"
    LANGUAGES CXX
)


if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_definitions(AGS_DEBUG)
    add_compile_definitions(AGS_APT_DEBUG)
    add_compile_definitions(AGS_ARE_DEBUG)
    add_compile_definitions(AGS_ARE_VK10_DEBUG)
    add_compile_definitions(AGS_ARE_GL43_DEBUG)
    add_compile_definitions(AGS_GEOMETRY_DEBUG)
    add_compile_definitions(AGS_IMAGE_DEBUG)
    add_compile_definitions(AGS_MESH_DEBUG)
    add_compile_definitions(AGS_PAINT_DEBUG)
    add_compile_definitions(AGS_UI_DEBUG)
    add_compile_definitions(AGS_VOXEL_DEBUG)
endif()



set(AGS_RENDER_API Vulkan10)
#set(AGS_RENDER_API OpenGL43)



if(${AGS_RENDER_API} STREQUAL "Vulkan10")
    add_compile_definitions(AGS_VULKAN10)
elseif(${AGS_RENDER_API} STREQUAL "OpenGL43")
    add_compile_definitions(AGS_OPENGL43)
else()
    message(FATAL_ERROR "No rendering API selected")
endif()



set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

## Include external libraries used for Vulkan rendering engine
if(${AGS_RENDER_API} STREQUAL "Vulkan10")
    add_subdirectory(external/glslang)
    add_subdirectory(external/SPIRV-Headers)
    add_subdirectory(external/SPIRV-Tools)

    set(SPIRV_REFLECT_EXAMPLES OFF)
    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set(SPIRV_REFLECT_ENABLE_ASSERTS OFF)
    endif()
    set(SPIRV_REFLECT_STATIC_LIB ON)
    add_subdirectory(external/SPIRV-Reflect)

    set(SHADERC_SKIP_TESTS True)
    cmake_policy(SET CMP0048 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0048 NEW) #The previous line doesn't seem to work. Scope error?
    add_subdirectory(external/shaderc/)
endif()

if(${AGS_RENDER_API} STREQUAL "OpenGL43")
    add_subdirectory(external/glad/)
endif()

# External libraries maintained by project author
add_subdirectory(external/AUL/)
add_subdirectory(external/AVML/)
add_subdirectory(external/AVEL/)

# Internal targets
add_subdirectory(internal/AGS/)
add_subdirectory(internal/AGS_core/)
add_subdirectory(internal/ui/)
add_subdirectory(internal/APT/)
add_subdirectory(internal/ARE/)
add_subdirectory(internal/image/)
add_subdirectory(internal/mesh/)
