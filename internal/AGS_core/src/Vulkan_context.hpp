//
// Created by avereniect on 1/17/22.
//

#ifndef AGS_VULKAN_CONTEXT_HPP
#define AGS_VULKAN_CONTEXT_HPP

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include <memory>

namespace ags {

    ///
    /// Enum representing for which purpose a queue family is best suited for
    ///
    enum class Queue_type {
        NULL_QUEUE_TYPE,
        GRAPHICS,
        COMPUTE,
        TRANSFER
    };

    ///
    /// Struct wrapping around
    ///
    struct Queue_family {

        //=================================================
        // -ctors
        //=================================================

        explicit Queue_family(vk::QueueFamilyProperties handle, Queue_type type);

        //=================================================
        // Instance members
        //=================================================

        vk::QueueFamilyProperties properties;

        Queue_type type;

    };

    struct Physical_device {

        //=================================================
        // -ctors
        //=================================================

        explicit Physical_device(vk::PhysicalDevice handle);

        Physical_device() = default;

        //=================================================
        // Instance members
        //=================================================

        vk::PhysicalDevice handle = VK_NULL_HANDLE;

        vk::PhysicalDeviceProperties properties{};

        vk::PhysicalDeviceFeatures features{};

        std::vector<Queue_family> queue_families{};

        //=================================================
        // Helper functions
        //=================================================

        static VkPhysicalDeviceProperties retrieve_properties(VkPhysicalDevice);

        static VkPhysicalDeviceFeatures retrieve_features(VkPhysicalDevice);

        static std::vector<Queue_family> retrieve_queue_families(VkPhysicalDevice);

    };

    /*
    struct Graphics_device {
        vk::Device handle;
        vk::PhysicalDevice physical_device;

        //vk::Queue display_queue;
        //std::uint32_t display_queue_index;

        vk::Queue graphics_queue;
        std::uint32_t graphics_queue_index;

        vk::Queue compute_queue;
        std::uint32_t compute_queue_index;

        vk::Queue transfer_queue;
        std::uint32_t transfer_queue_index;
    };

    struct Compute_device {
        vk::Device handle;

        vk::Queue compute_queue;
        vk::Queue transfer_queue;
    };
    */

    ///
    /// Class which manages Vulkan instance and associated state used by windows
    /// in the ui and ARE modules.
    ///
    class Vulkan_context {
    public:

        //=================================================
        // State methods
        //=================================================

        ///
        /// Perhaps setup work required for use by ARE and ui modules.
        ///
        ///
        static void init();

        static void term();

        //=================================================
        // Static members
        //=================================================

        static vk::Instance instance;

        ///
        /// Handle to dummy window.
        ///
        /// It is assumed that if a physical device can present to this window,
        /// then it can present to any other window.
        ///
        /// In practice, presenting is done to a window compositor, not to a
        /// real physical display so this assumption should hold in many cases.
        ///
        static GLFWwindow* dummy_window;

        ///
        /// Surface object for dummy window
        ///
        static VkSurfaceKHR dummy_surface;

        ///
        /// Device which should be used for the purpose of rendering graphics.
        ///
        //static Graphics_device graphics_device;

        ///
        /// Device which should be used for performing heavy general-purpose
        /// compute tasks.
        ///
        //static Compute_device heavy_compute_device;

        ///
        /// Device which should be used for light-weight general-purpose compute
        /// tasks.
        ///
        //static Compute_device light_compute_device;

        ///
        /// List of physical devices which were available when init() was called
        ///
        static std::vector<Physical_device> physical_devices;

        ///
        /// A list of extensions required by GLFW
        ///
        static std::vector<const char*> required_extensions;

        ///
        /// Format used for displaying on window
        ///
        static vk::SurfaceFormatKHR surface_format;

        ///
        /// List of available surface formats which graphics_device offers
        ///
        static std::vector<vk::SurfaceFormatKHR> surface_formats;

        ///
        /// Presentation mode which will be used by windows
        ///
        static vk::PresentModeKHR present_mode;

        ///
        /// List of required device extensions
        ///
        static constexpr std::array<const char*, 1> graphics_device_extensions{
            "VK_KHR_swapchain"
        };

        ///
        /// List of required instance extensions
        ///
        static constexpr std::array<const char*, 1> validation_layers{
            "VK_LAYER_KHRONOS_validation"
        };

    private:

        //=================================================
        // Helper functions
        //=================================================

        ///
        /// Create Vulkan instance object
        ///
        static void create_instance();

        ///
        /// Populates required_extensions
        ///
        static void retrieve_required_extensions();

        ///
        /// Ensures all validation layers specified in validation_layers are
        /// available
        ///
        static void verify_validation_layers();

        ///
        /// Populates physical_devices
        ///
        static void retrieve_physical_devices();

        ///
        ///
        /// \return Optimal physical device to use for graphics
        static Physical_device select_graphics_device();

        ///
        /// Populates graphics_device
        ///
        /// \param d Physical device used for rendering
        static void create_graphics_device(const Physical_device& d);

        ///
        /// \param d Physical device to hceck suitability of
        /// \return True if device is suitable for use a graphics device. False
        ///     otherwise
        static bool is_suitable_render_device(const Physical_device& d);

        ///
        /// Populates dummy_window and dummy_surface
        ///
        static void create_dummy_window();

    };

}

#endif //AGS_VULKAN_CONTEXT_HPP
