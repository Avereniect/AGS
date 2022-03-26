//
// Created by avereniect on 1/18/22.
//
#include "Windowing_context.hpp"

#include <GLFW/glfw3.h>

#include <iostream>

namespace ags {

    void Windowing_context::init() {
        glfwSetErrorCallback(Windowing_context::error_callback);
        if (!glfwInit()) {
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
        std::cerr << "GLFW error " << error_code << ":\n";
        std::cerr << message << '\n';
    }

}
