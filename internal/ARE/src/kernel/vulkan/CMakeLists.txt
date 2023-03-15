cmake_minimum_required(VERSION 3.13)

option(AGS_ARE_VULKAN_DEBUG OFF)

add_library(AGS_ARE_VULKAN STATIC
    Enums.hpp
    Enums.cpp

    ../Enums_common.hpp
    ../Enums_common.cpp

    ../Framebuffer_common.hpp

    Kernel.hpp
    Kernel.cpp

    Kernel_base.hpp
    Kernel_base.cpp

    Device_kernel.hpp
    Device_kernel.cpp

    Device.hpp
    Device.cpp

    Memory_kernel.hpp
    Memory_kernel.cpp

    Draw_call.hpp
    Draw_call.cpp

    Render_queue_kernel.hpp
    Render_queue_kernel.cpp

    Render_queue.hpp
    Render_queue.cpp

    Shader_kernel.hpp
    Shader_kernel.cpp

    Shader.hpp
    Shader.cpp

    Framebuffer_kernel.hpp
    Framebuffer_kernel.cpp

    Framebuffer.hpp
    Framebuffer.cpp

    Mesh_kernel.hpp
    Mesh_kernel.cpp

    Mesh.hpp
    Mesh.cpp

    Texture_kernel.hpp
    Texture_kernel.cpp

    Texture.hpp
    Texture.cpp
)

#find_library(glsl_path glslang PATHS ${PROJECT_SOURCE_DIR}/external/glslang NO_DEFAULT_PATH)
#message(FATAL_ERROR "glsl path: [" ${glsl_path} "]")

target_link_libraries(AGS_ARE_VULKAN
    PUBLIC AGS_mesh vulkan SPIRV glslang
)

#find_library(glslang_path glslang HINTS NO_SYSTEM_ENVIRONMENT_PATH NO_CACHE)
#message(FATAL_ERROR "glslang_path:[" ${glslang_path} "]")

if (AGS_ARE_VULKAN_DEBUG)
    target_compile_definitions(AGS_ARE_VULKAN
        PRIVATE AGS_ARE_VULKAN_DEBUG
    )
endif()

target_compile_definitions(AGS_ARE_VULKAN
    PRIVATE AGS_MODULE_NAME="AGS_ARE_VULKAN"
)

set_target_properties(AGS_ARE_VULKAN PROPERTIES LINKER_LANGUAGE CXX)
