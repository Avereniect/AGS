//
// Created by avereniect on 12/12/21.
//
#include "Windowing_context.hpp"

#include <iostream>
#include <iomanip>
#include <cstring>
#include <array>
#include <memory>
#include <vector>

namespace ags::windowing {

    #ifdef AGS_VULKAN10
    vk::Instance Windowing_context::instance{};

    #ifdef AGS_DEBUG
    std::array<const char*, 1> Windowing_context::validation_layers{
        "VK_LAYER_KHRONOS_validation"
    };
    #else
    std::array<const char*, 1> Windowing_context::validation_layers;
    #endif

    std::vector<const char*> Windowing_context::required_extensions{};

    GLFWwindow* Windowing_context::dummy = nullptr;

    #endif

    //=====================================================
    // Static members
    //=====================================================

    bool Windowing_context::is_initialized = false;

    //=====================================================
    // State initialization
    //=====================================================

    bool Windowing_context::init() {
        if (is_initialized) {
            return false;
        }

        glfwSetErrorCallback(Windowing_context::error_callback);

        if (glfwInit() != GLFW_TRUE) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }

        #ifdef AGS_VULKAN10
        create_dummy_window();
        create_vulkan_instance();

        #endif

        is_initialized = true;
        return true;
    }

    void Windowing_context::term() {
        if (!is_initialized) {
            return;
        }

        #ifdef AGS_VULKAN10
        instance.destroy();
        glfwDestroyWindow(dummy);
        #endif

        glfwTerminate();


        is_initialized = false;
    }

    //=====================================================
    // Misc.
    //=====================================================

    void Windowing_context::poll_events() {
        glfwPollEvents();
    }

    #ifdef AGS_VULKAN10

    const vk::Instance& Windowing_context::get_instance() {
        return instance;
    }

    #endif

    //=====================================================
    // Helper functions
    //=====================================================

    void Windowing_context::create_vulkan_instance() {
        #ifdef AGS_DEBUG
        if (!verify_validation_layers()) {
            return;
        }
        #endif

        vk::ApplicationInfo application_info {
            "AGS",
            VK_MAKE_VERSION(1, 0, 0),
            nullptr,
            VK_MAKE_VERSION(0, 0, 0),
            VK_API_VERSION_1_0
        };

        std::uint32_t required_extension_count;
        const char** const required_extension_names = glfwGetRequiredInstanceExtensions(&required_extension_count);
        required_extensions.resize(required_extension_count);
        std::copy_n(required_extension_names, required_extension_count, required_extensions.data());

        vk::InstanceCreateInfo instance_create_info{
            {},
            &application_info,
            validation_layers,
            required_extensions
        };

        instance = vk::createInstance(instance_create_info);
    }

    bool Windowing_context::verify_validation_layers() {
        std::uint32_t available_validation_layer_count;
        vkEnumerateInstanceLayerProperties(
            &available_validation_layer_count,
            nullptr
        );

        std::vector<VkLayerProperties> available_layers;
        available_layers.resize(available_validation_layer_count);

        vkEnumerateInstanceLayerProperties(
            &available_validation_layer_count,
            available_layers.data()
        );

        //TODO: Replace with alternative with better time complexity
        for (auto name : validation_layers) {
            bool layer_found = false;
            for (auto layer_properties : available_layers) {
                layer_found |= (strcmp(name, layer_properties.layerName) == 0);
            }

            if (!layer_found) {
                std::cerr << "Could not find requested validation layer: " << name << std::endl;
                return false;
            }
        }

        return true;
    }

    void Windowing_context::create_dummy_window() {
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        dummy = glfwCreateWindow(1, 1, "Dummy", nullptr, nullptr);
    }

    //=====================================================
    // Callbacks
    //=====================================================

    void Windowing_context::error_callback(int error, const char* message) {
        std::cerr << "GLFW error: " << std::hex << error << ' ' << message << std::endl;
    }

}
