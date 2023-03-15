#include "Memory_kernel.hpp"

#include <ags/Logging.hpp>

namespace ags::are::vk_kernel {

    //=====================================================
    // Static members
    //=====================================================

    std::vector<Heap> Memory_kernel::heaps{};

    std::uint32_t Memory_kernel::image_memory_index = 0;

    //=====================================================
    // State functions
    //=====================================================

    void Memory_kernel::init() {
        retrieve_heaps();

        auto properties = graphics_device.physical_device.getMemoryProperties();

        // Identify memory type index for images
        for (std::size_t i = 0; i < properties.memoryTypes.size(); ++i) {
            auto flags = properties.memoryTypes[i].propertyFlags;
            auto suitable = (flags & vk::MemoryPropertyFlagBits::eDeviceLocal);
            if (suitable) {
                image_memory_index = i;
            }
        }
    }

    void Memory_kernel::term() {

    }

    //=====================================================
    // Helper functions
    //=====================================================

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

    void Memory_kernel::allocate_image_memory(vk::Image image, Buffer_usage usage) {
        auto memory_requirements = graphics_device.handle.getImageMemoryRequirements(image);

        //TODO: Leverage buffer usage parameter


        auto properties = graphics_device.physical_device.getMemoryProperties();

        // Identify memory type index for images
        for (std::size_t i = 0; i < properties.memoryTypes.size(); ++i) {
            auto flags = properties.memoryTypes[i].propertyFlags;
            auto bit_set = memory_requirements.memoryTypeBits & (1 << i);
            auto suitable = bit_set && (flags & vk::MemoryPropertyFlagBits::eDeviceLocal);
            if (suitable) {
                image_memory_index = i;
            }
        }

        vk::MemoryAllocateInfo allocation_info{
            memory_requirements.size,
            image_memory_index
        };

        vk::DeviceMemory allocation = graphics_device.handle.allocateMemory(allocation_info);
        graphics_device.handle.bindImageMemory(image, allocation, 0);
    }

}
