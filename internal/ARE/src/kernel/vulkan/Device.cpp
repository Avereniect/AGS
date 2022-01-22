//
// Created by avereniect on 1/16/22.
//
#include "Device.hpp"

#include <cstdint>

namespace  ags::are::vk10 {

    Queue_type classify_queue(VkQueueFamilyProperties properties) {
        auto flags = properties.queueFlags;

        //TODO: Check for presentation support
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

    Queue_family::Queue_family(vk::QueueFamilyProperties p, Queue_type type):
        properties(p),
        type(type) {}

    Physical_device::Physical_device(vk::PhysicalDevice handle):
        handle(handle),
        properties(retrieve_properties(handle)),
        features(retrieve_features(handle)),
        queue_families(retrieve_queue_families(handle)) {}

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

}