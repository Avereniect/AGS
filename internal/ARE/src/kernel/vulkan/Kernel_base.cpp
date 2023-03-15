#include "Kernel_base.hpp"

#include <ags/Logging.hpp>

#include <cstdint>

namespace ags::are::vk_kernel {

    //=====================================================
    // Static members
    //=====================================================

    VkInstance Kernel_base::instance{};

    std::vector<const char*> Kernel_base::required_extensions{};

    std::vector<const char*> Kernel_base::validation_layers{
        "VK_LAYER_KHRONOS_validation"
    };

    GLFWwindow* Kernel_base::dummy_window = nullptr;

    vk::SurfaceKHR Kernel_base::dummy_surface;

    vk::SurfaceFormatKHR Kernel_base::surface_format;

    vk::Format Kernel_base::presentation_format;

    vk::ColorSpaceKHR Kernel_base::presentation_colorspace;

    vk::PresentModeKHR Kernel_base::presentation_mode;

    //=====================================================
    // State methods
    //=====================================================

    void Kernel_base::init() {
        retrieve_required_extensions();
        verify_validation_layers();
        create_instance();
        create_dummy_window();

        surface_format.colorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;
        surface_format.format = vk::Format::eB8G8R8A8Srgb;

        presentation_format = vk::Format::eB8G8R8A8Srgb;
        presentation_colorspace = vk::ColorSpaceKHR::eSrgbNonlinear;
        presentation_mode = vk::PresentModeKHR::eFifo;
    }

    void Kernel_base::term() {
        //TODO: Release acquired resources

    }

    //=====================================================
    // Accessors
    //=====================================================

    VkInstance Kernel_base::get_instance() {
        return instance;
    }

    vk::SurfaceFormatKHR Kernel_base::get_surface_format() {
        return surface_format;
    }

    vk::Format Kernel_base::get_presentation_format() {
        return presentation_format;
    }

    vk::ColorSpaceKHR Kernel_base::get_presentation_colorspace() {
        return presentation_colorspace;
    }

    vk::PresentModeKHR Kernel_base::get_presentation_mode() {
        return presentation_mode;
    }

    //=====================================================
    // Helper functions
    //=====================================================

    void Kernel_base::retrieve_required_extensions() {
        std::uint32_t req_extension_count;
        const char** req_extensions = glfwGetRequiredInstanceExtensions(&req_extension_count);

        required_extensions.resize(req_extension_count);
        std::copy_n(req_extensions, req_extension_count, required_extensions.data());
    }

    void Kernel_base::verify_validation_layers() {
        std::uint32_t available_validation_layer_count;
        auto r0 = vk::enumerateInstanceLayerProperties(
            &available_validation_layer_count,
            nullptr
        );

        std::vector<vk::LayerProperties> available_layers;
        available_layers.resize(available_validation_layer_count);

        auto r1 = vk::enumerateInstanceLayerProperties(
            &available_validation_layer_count,
            available_layers.data()
        );


        //TODO: Replace with alternative with better time complexity
        for (auto name : validation_layers) {
            bool layer_found = false;
            for (auto layer_properties : available_layers) {
                int t = strcmp(name, layer_properties.layerName);
                if (t == 0) {
                    layer_found = true;
                    break;
                }
            }

            if (!layer_found) {
                AGS_FATAL("Fatal error encountered at {}\n{}{}", AGS_CODE_LOCATION, "Could not find requested validation layer: ", name);
                exit(EXIT_FAILURE);
            }
        }
    }

    void Kernel_base::create_instance() {
        vk::ApplicationInfo application_info {
            "AGS",
            VK_MAKE_VERSION(1, 0, 0),
            nullptr,
            VK_MAKE_VERSION(0, 0, 0),
            VK_API_VERSION_1_0
        };

        vk::InstanceCreateInfo instance_create_info{
            {},
            &application_info,
            validation_layers,
            required_extensions
        };

        instance = vk::createInstance(instance_create_info);
    }

    void Kernel_base::create_dummy_window() {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        dummy_window = glfwCreateWindow(1, 1, "AGS dummy", nullptr, nullptr);
        if (!dummy_window) {
            throw std::runtime_error("Vulkan Context: Failed to create dummy window");
        }

        VkSurfaceKHR tmp_surface;

        VkResult r = glfwCreateWindowSurface(instance, dummy_window, nullptr, &tmp_surface);
        if (r != VK_SUCCESS) {
            throw std::runtime_error("Failed to create dummy window surface");
        }

        dummy_surface = tmp_surface;
    }

}