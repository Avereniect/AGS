//
// Created by avereniect on 1/18/22.
//
#include "Core.hpp"

#include "Windowing_context.hpp"
#ifdef AGS_VULKAN10
#include "Vulkan_context.hpp"
#endif

#include <GLFW/glfw3.h>
#include <iostream>

namespace ags {

    bool Core::is_initialized = false;

    void Core::init() {
        if (is_initialized) {
            return;
        }

        Windowing_context::init();
        Vulkan_context::init();

        is_initialized = true;
    }

    void Core::term() {
        if (!is_initialized) {
            return;
        }

        Vulkan_context::term();
        Windowing_context::term();

        is_initialized = false;
    }

}
