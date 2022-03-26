//
// Created by avereniect on 12/11/21.
//

#include "Engine.hpp"

#include <ags/Vulkan_core.hpp>
#include <ags/Window_core.hpp>
#include <ags/ARE.hpp>

namespace ags {

    bool Engine::is_initialized = false;

    bool Engine::init() {
        if (is_initialized) {
            return false;
        }

        ags::Windowing_context::init();
        are::ARE::init();

        is_initialized = true;
        return true;
    }

    void Engine::term() {
        if (!is_initialized) {
            return;
        }

        are::ARE::term();
        Windowing_context::term();

        is_initialized = false;
    }

}
