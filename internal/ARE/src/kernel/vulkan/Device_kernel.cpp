#include "Device_kernel.hpp"
#include <cstdint>

namespace ags::are::vk_kernel {

    //=====================================================
    // Static members
    //=====================================================

    Graphics_device Device_kernel::graphics_device{};

    Compute_device Device_kernel::heavy_compute_device{};

    Compute_device Device_kernel::light_compute_device{};

    std::vector<Physical_device> Device_kernel::physical_devices{};

    //=====================================================
    // State methods
    //=====================================================

    bool Device_kernel::init() {
        retrieve_physical_devices();
        create_graphics_device(select_graphics_device());
        //create_heavy_compute_device(select_heavy_compute_device());
        //create_light_compute_device(select_light_compute_device());

        return false;
    }

    void Device_kernel::term() {
        graphics_device.handle.destroy();
        heavy_compute_device.handle.destroy();
        light_compute_device.handle.destroy();
    }

    //=====================================================
    // Accessors
    //=====================================================

    const Graphics_device& Device_kernel::get_graphics_device() {
        return graphics_device;
    }

    const Compute_device& Device_kernel::get_heavy_compute_device() {
        return heavy_compute_device;
    }

    const Compute_device& Device_kernel::get_light_compute_device() {
        return light_compute_device;
    }

    //=====================================================
    // Helper functions
    //=====================================================

    void Device_kernel::retrieve_physical_devices() {
        std::vector<VkPhysicalDevice> tmp;

        std::uint32_t physical_device_count;
        vkEnumeratePhysicalDevices(
            instance,
            &physical_device_count,
            nullptr
        );

        if (physical_device_count == 0) {
            throw std::runtime_error("No physical devices could be retrieved.");
        }

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
        std::vector<std::reference_wrapper<const Physical_device>> candidates;
        for (const auto& d : physical_devices) {
            if (is_suitable_graphics_device(d)) {
                candidates.emplace_back(d);
            }
        }

        if (candidates.empty()) {
            throw std::runtime_error("No devices were suitable for rendering graphics.");
        } else {
            //TODO: Select most suitable device
            return candidates[0];
        }
    }

    /*
    Physical_device Device_kernel::select_heavy_compute_device() {
        std::vector<std::reference_wrapper<const Physical_device>> candidates;
        for (const auto& d : physical_devices) {
            if (is_suitable_heavy_compute_device(d)) {
                candidates.emplace_back(d);
            }
        }

        if (candidates.empty()) {
            throw std::runtime_error("No devices were suitable for use as a heavy compute deivce");
        } else {
            //TODO: Select most suitable device
            return candidates[0];
        }
    }
    */

    /*
    Physical_device Device_kernel::select_light_compute_device() {
        std::vector<std::reference_wrapper<const Physical_device>> candidates;
        for (const auto& d : physical_devices) {
            if (is_suitable_light_compute_device(d)) {
                candidates.emplace_back(d);
            }
        }

        if (candidates.empty()) {
            throw std::runtime_error("No devices were suitable for use as a heavy compute deivce");
        } else {
            //TODO: Select most suitable device
            return candidates[0];
        }
    }
    */

    void Device_kernel::create_graphics_device(const Physical_device& d) {
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
        graphics_device.physical_device = d.handle;

        for (std::uint32_t i = 0; i < d.queue_families.size(); ++i) {
            if (d.queue_families[i].type == Queue_type::GRAPHICS) {
                graphics_device.graphics_queue = graphics_device.handle.getQueue(i, 0);
                graphics_device.graphics_queue_index = i;
                break;
            }
        }

        for (std::uint32_t i = 0; i < d.queue_families.size(); ++i) {
            if (d.queue_families[i].type == Queue_type::COMPUTE) {
                graphics_device.compute_queue = graphics_device.handle.getQueue(i, 0);
                graphics_device.compute_queue_index = i;
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

    bool Device_kernel::is_suitable_graphics_device(const Physical_device& d) {
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

        //Check that physical device supports required surface format
        //Note: It is assumed that if the device supports a particular format
        //for the dummy surface then it supports that format for all surfaces
        //which perhaps it doesn't.
        std::uint32_t format_count;
        auto t0 = d.handle.getSurfaceFormatsKHR(dummy_surface, &format_count, nullptr);

        std::vector<vk::SurfaceFormatKHR> formats;
        formats.resize(format_count);
        auto t1 = d.handle.getSurfaceFormatsKHR(dummy_surface, &format_count, formats.data());

        bool required_format_found = false;
        for (auto f : formats) {
            if (f == surface_format) {
                required_format_found = true;
                break;
            }
        }

        if (!required_format_found) {
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
