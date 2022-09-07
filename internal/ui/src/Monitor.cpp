//
// Created by avereniect on 6/16/22.
//
#include "Monitor.hpp"

namespace ags::ui {

    void Monitors::init() {
        int monitor_count;
        GLFWmonitor** monitor_pointers = glfwGetMonitors(&monitor_count);


    }


    void Monitors::monitor_callback(GLFWmonitor* handle, int event) {
        if (event == GLFW_CONNECTED) {

        }

        if (event == GLFW_DISCONNECTED) {
            auto it0 = monitors.begin();
            auto it1 = monitors.end();

            for (;it0 != it1; ++it0) {
                if (it0->handle == handle) {
                    monitors.erase(it0);
                    return;
                }
            }

        }
    }

}
