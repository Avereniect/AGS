//
// Created by avereniect on 1/13/22.
//
#include "Device_kernel.hpp"
#include <cstdint>

namespace ags::are::vk10 {

    //=====================================================
    // Static members
    //=====================================================

    vk::Device Device_kernel::graphics_device;
    vk::Queue Device_kernel::graphics_work_queue;
    vk::Queue Device_kernel::graphics_compute_queue;
    vk::Queue Device_kernel::graphics_transfer_queue;

    std::vector<Physical_device> Device_kernel::physical_devices;

    //=====================================================
    // State methods
    //=====================================================

    bool Device_kernel::init() {
        retrieve_physical_devices();
        graphics_device = create_graphics_device(select_graphics_device());
        return false;
    }

    void Device_kernel::term() {
        graphics_device.destroy();
    }

    void Device_kernel::retrieve_physical_devices() {
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

    Physical_device Device_kernel::select_graphics_device() {
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

    void Device_kernel::create_graphics_device(const Physical_device& d) {
        std::vector<vk::DeviceQueueCreateInfo> queue_create_infos{};
        queue_create_infos.reserve(d.queue_families.size());

        //TODO: Handle theoretical case where device has more than three families

        float priority = 0.5f;
        for (std::uint32_t i = 0; i < d.queue_families.size(); ++i) {
            queue_create_infos.emplace_back(
                vk::DeviceQueueCreateFlagBits{},
                i,
                1, //TODO: Verify that one is enough
                &priority
            );
        }

        vk::DeviceCreateInfo device_create_info{
            {},
            static_cast<uint32_t>(d.queue_families.size()),
            queue_create_infos.data(),
            0,
            nullptr,
            0,
            nullptr
        };

        graphics_device = d.handle.createDevice(device_create_info);

        for (std::uint32_t i = 0; i < d.queue_families.size(); ++i) {
            if (d.queue_families[i].type == Queue_type::GRAPHICS) {
                graphics_work_queue = graphics_device.getQueue(i, 0);
                break;
            }
        }

        for (std::uint32_t i = 0; i < d.queue_families.size(); ++i) {
            if (d.queue_families[i].type == Queue_type::COMPUTE) {
                graphics_compute_queue = graphics_device.getQueue(i, 0);
                break;
            }
        }

        for (std::uint32_t i = 0; i < d.queue_families.size(); ++i) {
            if (d.queue_families[i].type == Queue_type::TRANSFER) {
                graphics_transfer_queue = graphics_device.getQueue(i, 0);
                break;
            }
        }
    }

    bool Device_kernel::is_suitable_render_device(const Physical_device& d) {
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

        bool has_graphics_queue = false;
        bool has_compute_queue = false;
        bool has_transfer_queue = false;

        //Check that there are queues with the appropriate capabilities
        for (auto q : d.queue_families) {
            has_graphics_queue |= (q.type == Queue_type::GRAPHICS);
            has_compute_queue  |= (q.type == Queue_type::COMPUTE );
            has_transfer_queue |= (q.type == Queue_type::TRANSFER);
        }

        return
            has_graphics_queue &&
            has_compute_queue &&
            has_transfer_queue;
    }

}
