//
// Created by avereniect on 6/23/22.
//

#ifndef AGS_GRAPHICS_INCLUDES_HPP
#define AGS_GRAPHICS_INCLUDES_HPP

#if defined(AGS_OPENGL)
#include <glad/glad.h>
#endif

#if defined(AGS_VULKAN)
#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp>
#endif

#include <GLFW/glfw3.h>

#endif //AGS_GRAPHICS_INCLUDES_HPP
