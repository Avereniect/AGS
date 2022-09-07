//
// Created by avereniect on 1/13/22.
//

#ifndef AGS_ARE_VK_KERNEL_BASE_HPP
#define AGS_ARE_VK_KERNEL_BASE_HPP

#include <ags/Graphics_includes.hpp>

#include <vector>
#include <string>

namespace ags::are::vk_kernel {

    class Kernel_base {
    public:

        //=================================================
        // State methods
        //=================================================

        static void init();

        static void term();

        //=================================================
        // Accessors
        //=================================================

        static VkInstance get_instance();

        static vk::SurfaceFormatKHR get_surface_format();

        static vk::Format get_presentation_format();

        static vk::ColorSpaceKHR get_presentation_colorspace();

        static vk::PresentModeKHR get_presentation_mode();

    protected:

        //=================================================
        // Static members
        //=================================================

        static VkInstance instance;

        static std::vector<const char*> required_extensions;

        static std::vector<const char*> validation_layers;

        static GLFWwindow* dummy_window;

        static vk::SurfaceKHR dummy_surface;

        static vk::SurfaceFormatKHR surface_format;

        static vk::Format presentation_format;

        static vk::ColorSpaceKHR presentation_colorspace;

        static vk::PresentModeKHR presentation_mode;

    private:

        //=================================================
        // Helper functions
        //=================================================

        ///
        /// \return Vector containing array containing the Vulkan extensions
        /// required by GLFW
        static void retrieve_required_extensions();

        ///
        /// Ensures all validation layers specified in validation_layers are
        /// available.
        ///
        /// Throws an exception upon failure
        ///
        static void verify_validation_layers();

        ///
        /// \return Newly created Vulkan instance handle
        static void create_instance();

        ///
        /// \return Handle to newly created window
        static void create_dummy_window();

    };

}

#endif //AGS_VK_KERNEL_BASE_HPP
