//
// Created by avereniect on 1/18/22.
//
#include "Windowing_context.hpp"

#include "ags/Logging.hpp"
#include <ags/Graphics_includes.hpp>

#include <string>

namespace ags {

    void Windowing_context::init() {
        glfwSetErrorCallback(Windowing_context::error_callback);
        if (!glfwInit()) {
            AGS_FATAL("Failed to initialize GLFW library");
            throw std::runtime_error("Failed to initialized GLFW library.");
        }
    }

    void Windowing_context::term() {
        glfwTerminate();
    }

    void Windowing_context::poll_events() {
        glfwPollEvents();
    }

    void Windowing_context::error_callback(int error_code, const char* message) {
        AGS_ERROR("GLFW error code: {}\n {}", error_code, message);
    }

}
