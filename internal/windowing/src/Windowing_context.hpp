//
// Created by avereniect on 12/12/21.
//

#ifndef AGS_WINDOWING_CONTEXT_HPP
#define AGS_WINDOWING_CONTEXT_HPP

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>
//#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>

#include "ags/Enums.hpp"

namespace ags::windowing {

    class Window;

    ///
    /// Singleton-manager for state of GLFW library
    ///
    class Windowing_context {
        friend class Window;
    public:

        //=================================================
        // State initialization
        //=================================================

        ///
        /// Initializes GLFW library
        ///
        /// \return True if initialization succeeds. False if fails to
        ///     initialize for any reason
        static bool init();

        ///
        /// Terminates GLFW library
        ///
        static void term();

        //=================================================
        // Misc.
        //=================================================

        ///
        /// Poll for input events
        ///
        static void poll_events();

        #ifdef AGS_VULKAN10

        static const vk::Instance& get_instance();

        #endif

    private:

        //=================================================
        // Static members
        //=================================================

        static bool is_initialized;

        #ifdef AGS_VULKAN10
        static vk::Instance instance;

        static std::array<const char*, 1> validation_layers;
        static std::vector<const char*> required_extensions;

        ///
        /// Dummy window used for testing whether chosen physical device can
        /// present. It is assumed that if the device can present to this window
        /// then it can present to any window owned by ags::windowing::Window
        /// objects.
        ///
        /// This assumption may not hold. Consider testing multiple monitors.
        ///
        static GLFWwindow* dummy;

        #endif

        //=================================================
        // Helper functions
        //=================================================

        #ifdef AGS_VULKAN10

        static void create_vulkan_instance();

        static bool verify_validation_layers();

        static void create_dummy_window();

        #endif

        //=================================================
        // Callbacks
        //=================================================

        static void error_callback(int error, const char* message);

    };

}

#endif //AGS_WINDOWING_CONTEXT_HPP
