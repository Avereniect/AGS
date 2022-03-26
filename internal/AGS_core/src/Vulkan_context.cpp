//
// Created by avereniect on 1/18/22.
//
#include "Vulkan_context.hpp"

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

namespace ags {

    Queue_family::Queue_family(vk::QueueFamilyProperties p, Queue_type type):
        properties(p),
        type(type) {}

    Queue_type classify_queue(VkQueueFamilyProperties properties) {
        auto flags = properties.queueFlags;

        bool has_graphics = (flags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT);
        bool has_compute  = (flags & VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT);
        bool has_transfer = (flags & VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT);

        if (has_graphics && has_compute && has_transfer) {
            return Queue_type::GRAPHICS;
        }

        if (has_compute && has_transfer) {
            return Queue_type::COMPUTE;
        }

        if (has_transfer) {
            return Queue_type::TRANSFER;
        }

        return Queue_type::NULL_QUEUE_TYPE;
    }

    VkPhysicalDeviceProperties Physical_device::retrieve_properties(VkPhysicalDevice d) {
        VkPhysicalDeviceProperties ret;
        vkGetPhysicalDeviceProperties(d, &ret);
        return ret;
    }

    VkPhysicalDeviceFeatures Physical_device::retrieve_features(VkPhysicalDevice d) {
        VkPhysicalDeviceFeatures ret;
        vkGetPhysicalDeviceFeatures(d, &ret);
        return ret;
    }

    std::vector<Queue_family> Physical_device::retrieve_queue_families(VkPhysicalDevice d) {
        std::vector<Queue_family> ret;

        std::vector<VkQueueFamilyProperties> tmp;
        std::uint32_t q_count;
        vkGetPhysicalDeviceQueueFamilyProperties(d, &q_count, nullptr);
        tmp.resize(q_count);
        vkGetPhysicalDeviceQueueFamilyProperties(d, &q_count, tmp.data());

        tmp.reserve(q_count);
        for (auto q : tmp) {
            ret.emplace_back(q, classify_queue(q));
        }

        return ret;
    }

    Physical_device::Physical_device(vk::PhysicalDevice handle):
        handle(handle),
        properties(retrieve_properties(handle)),
        features(retrieve_features(handle)),
        queue_families(retrieve_queue_families(handle)) {}

    //=====================================================
    // Static members
    //=====================================================

    vk::Instance Vulkan_context::instance{};

    GLFWwindow* Vulkan_context::dummy_window = nullptr;
    VkSurfaceKHR Vulkan_context::dummy_surface{};

    std::vector<Physical_device> Vulkan_context::physical_devices{};

    std::vector<const char*> Vulkan_context::required_extensions{};

    vk::SurfaceFormatKHR Vulkan_context::surface_format{};

    std::vector<vk::SurfaceFormatKHR> Vulkan_context::surface_formats{};

    vk::PresentModeKHR Vulkan_context::present_mode{};

    //=====================================================
    // State functions
    //=====================================================

    void Vulkan_context::init() {
        retrieve_required_extensions();
        verify_validation_layers();
        create_instance();
        create_dummy_window();
        retrieve_physical_devices();
        create_graphics_device(select_graphics_device());
    }

    void Vulkan_context::term() {
    }

    void Vulkan_context::create_instance() {
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

    void Vulkan_context::retrieve_required_extensions() {
        std::uint32_t required_extension_count;
        const char** const required_extension_names = glfwGetRequiredInstanceExtensions(&required_extension_count);
        required_extensions.resize(required_extension_count);
        std::copy_n(required_extension_names, required_extension_count, required_extensions.data());
    }

    void Vulkan_context::verify_validation_layers() {
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
                std::string error_message{"Could not find requested validation layer: ", name};
                throw std::runtime_error(error_message);
            }
        }
    }

    void Vulkan_context::retrieve_physical_devices() {
        std::vector<VkPhysicalDevice> tmp;

        std::uint32_t physical_device_count;
        vkEnumeratePhysicalDevices(
            instance,
            &physical_device_count,
            nullptr
        );

        tmp.resize(physical_device_count);
        vkEnumeratePhysicalDevices(
            instance,
            &physical_device_count,
            tmp.data()
        );

        physical_devices.reserve(physical_device_count);

        for (auto h : tmp) {
            physical_devices.emplace_back(h);
        }
    }

    Physical_device Vulkan_context::select_graphics_device() {
        std::vector<Physical_device> candidates;
        for (const auto& d : physical_devices) {
            if (is_suitable_render_device(d)) {
                candidates.emplace_back(d);
            }
        }

        if (candidates.empty()) {
            //TODO: Log or do something more. Throw an exception?
            return {};
        } else {
            return candidates[0];
        }
    }

    void Vulkan_context::create_graphics_device(const Physical_device& d) {
        std::vector<vk::DeviceQueueCreateInfo> queue_create_infos{};
        queue_create_infos.reserve(d.queue_families.size());

        //TODO: Handle theoretical case where device has more than three families

        float priority = 0.5f;
        for (std::uint32_t i = 0; i < d.queue_families.size(); ++i) {
            queue_create_infos.emplace_back(
                vk::DeviceQueueCreateFlagBits{},
                i,
                1, //TODO: Use more queues on certain GPU micro-architectures
                &priority
            );
        }

        vk::DeviceCreateInfo device_create_info{
            {},
            static_cast<uint32_t>(d.queue_families.size()),
            queue_create_infos.data(),
            0,
            nullptr,
            graphics_device_extensions.size(),
            graphics_device_extensions.data()
        };

        graphics_device.handle = d.handle.createDevice(device_create_info);

        for (std::uint32_t i = 0; i < d.queue_families.size(); ++i) {
            if (d.queue_families[i].type == Queue_type::GRAPHICS) {
                graphics_device.graphics_queue = graphics_device.handle.getQueue(i, 0);
                graphics_device.compute_queue_index = i;
                break;
            }
        }

        for (std::uint32_t i = 0; i < d.queue_families.size(); ++i) {
            if (d.queue_families[i].type == Queue_type::COMPUTE) {
                graphics_device.compute_queue = graphics_device.handle.getQueue(i, 0);
                graphics_device.compute_queue_index = i;
                break;
            }
        }

        for (std::uint32_t i = 0; i < d.queue_families.size(); ++i) {
            if (d.queue_families[i].type == Queue_type::TRANSFER) {
                graphics_device.transfer_queue = graphics_device.handle.getQueue(i, 0);
                graphics_device.transfer_queue_index = i;
                break;
            }
        }
    }

    bool Vulkan_context::is_suitable_render_device(const Physical_device& d) {
        // Ensure device is some kind of GPU
        // Avoid CPU and other devices.
        switch (d.properties.deviceType) {
        case vk::PhysicalDeviceType::eDiscreteGpu:
        case vk::PhysicalDeviceType::eVirtualGpu:
        case vk::PhysicalDeviceType::eIntegratedGpu:
            break;
        case vk::PhysicalDeviceType::eCpu:
        case vk::PhysicalDeviceType::eOther:
        default:
            return false;
        }

        //TODO: Handle testing of presentation support on theoretical card with
        // multiple render queue families

        bool graphics_queue_can_present = false;

        bool has_graphics_queue = false;
        bool has_compute_queue = false;
        bool has_transfer_queue = false;

        //Check that there are queues with the appropriate capabilities
        for (std::uint32_t i = 0; i < d.queue_families.size(); ++i) {
            auto& q = d.queue_families[i];

            has_graphics_queue |= (q.type == Queue_type::GRAPHICS);
            has_compute_queue  |= (q.type == Queue_type::COMPUTE );
            has_transfer_queue |= (q.type == Queue_type::TRANSFER);

            if (q.type == Queue_type::GRAPHICS) {
                VkBool32 can_present = false;
                vkGetPhysicalDeviceSurfaceSupportKHR(d.handle, i, dummy_surface, &can_present);
                graphics_queue_can_present |= can_present;
            }
        }

        return
            graphics_queue_can_present &&
            has_graphics_queue &&
            has_compute_queue &&
            has_transfer_queue;
    }

    void Vulkan_context::create_dummy_window() {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        dummy_window = glfwCreateWindow(1, 1, "AGS dummy", nullptr, nullptr);
        if (!dummy_window) {
            throw std::runtime_error("Vulkan Context: Failed to create dummy window");
        }

        VkResult r = glfwCreateWindowSurface(instance, dummy_window, nullptr, &dummy_surface);
        if (r != VK_SUCCESS) {
            throw std::runtime_error("Failed to create dummy window surface");
        }
    }

}
