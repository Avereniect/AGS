//
// Created by avereniect on 1/16/22.
//

#ifndef AGS_ARE_VK_DEVICE_HPP
#define AGS_ARE_VK_DEVICE_HPP

#include <ags/Graphics_includes.hpp>

#include <vector>

namespace ags::are::vk_kernel {

    //=====================================================
    // Enums
    //=====================================================

    enum class Queue_type {
        NULL_QUEUE_TYPE,
        GRAPHICS,
        COMPUTE,
        TRANSFER
    };

    Queue_type classify_queue(vk::QueueFamilyProperties p);

    enum class Vendor {
        NULL_VENDOR,
        INTEL,
        NVIDIA,
        AMD
    };





    struct Queue_family {

        //=================================================
        // -ctors
        //=================================================

        explicit Queue_family(vk::QueueFamilyProperties handle, Queue_type type);

        //=================================================
        // Instance members
        //=================================================

        vk::QueueFamilyProperties properties{};

        Queue_type type = Queue_type::NULL_QUEUE_TYPE;

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

    struct Graphics_device {
        vk::Device handle = VK_NULL_HANDLE;
        vk::PhysicalDevice physical_device = VK_NULL_HANDLE;

        vk::Queue graphics_queue = VK_NULL_HANDLE;
        std::uint32_t graphics_queue_index = 0;

        vk::Queue compute_queue = VK_NULL_HANDLE;
        std::uint32_t compute_queue_index = 0;

        vk::Queue transfer_queue = VK_NULL_HANDLE;
        std::uint32_t transfer_queue_index = 0;
    };

    struct Compute_device {
        vk::Device handle = VK_NULL_HANDLE;

        vk::Queue compute_queue = VK_NULL_HANDLE;
        std::uint32_t compute_queue_index = 0;

        vk::Queue transfer_queue = VK_NULL_HANDLE;
        std::uint32_t transfer_queue_index = 0;
    };

}

#endif //AGS_ARE_VK10_DEVICE_HPP
