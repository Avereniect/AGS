//
// Created by avereniect on 1/16/22.
//

#ifndef AGS_DEVICE_HPP
#define AGS_DEVICE_HPP

#include <vulkan/vulkan.hpp>

#include <vector>

namespace ags::are::vk10 {

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

}

#endif //AGS_DEVICE_HPP
