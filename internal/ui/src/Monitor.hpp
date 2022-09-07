//
// Created by avereniect on 6/16/22.
//

#ifndef AGS_MONITOR_HPP
#define AGS_MONITOR_HPP

#if defined(AGS_UI_VULKAN)
    #include <vulkan/vulkan.hpp>
#endif

#if defined(AGS_UI_OPENGL)
    #include <glad/glad.h>
#endif

#include <vector>

namespace ags::ui {

    class Monitor;

    class Monitors {
    public:

        static void init();

        static void term();


    private:

        //=================================================
        // Static members
        //=================================================

        static std::vector<Monitor> monitors;

        //=================================================
        // Callbacks
        //=================================================

        static void monitor_callback(GLFWmonitor* handle, int event);

    };

    class Monitor {
        friend class Monitors;
    public:

        //=================================================
        // -ctors
        //=================================================

        //=================================================
        // Assignment Operators
        //=================================================

        //=================================================
        // Accessors
        //=================================================

        //=================================================
        // Conversion Operators
        //=================================================

    private:

        //=================================================
        // Instance members
        //=================================================

        GLFWmonitor* handle = nullptr;

    };

}

#endif //AGS_MONITOR_HPP
