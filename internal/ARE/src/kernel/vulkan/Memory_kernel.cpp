//
// Created by avereniect on 3/16/22.
//
#include "Memory_kernel.hpp"

#include <ags/Logging.hpp>

namespace ags::are::vk_kernel {

    void Memory_kernel::init() {
        retrieve_heaps();
    }

    void Memory_kernel::term() {

    }

    void Memory_kernel::retrieve_heaps() {
        auto memory_properties = graphics_device.physical_device.getMemoryProperties();
        heaps.resize(memory_properties.memoryHeapCount);
    }

    vk::Buffer Memory_kernel::create_vertex_buffer(std::uint32_t n, Buffer_usage usage) {
        std::array<std::uint32_t, 1> queue_indices{
            Device_kernel::get_graphics_device().graphics_queue_index
        };

        vk::BufferCreateInfo buffer_create_info{
            vk::BufferCreateFlagBits{},
            vk::DeviceSize{n},
            vk::BufferUsageFlagBits::eVertexBuffer,
            vk::SharingMode::eExclusive,
            queue_indices
        };

        vk::Buffer ret = Device_kernel::get_graphics_device().handle.createBuffer(buffer_create_info);

        if (!ret) {
            AGS_ERROR("Error encountered at {}\n{}\n", AGS_CODE_LOCATION, "Failed to create vertex buffer");
            return {VK_NULL_HANDLE};
        }

        return ret;
    }



}
