//
// Created by avereniect on 3/16/22.
//
#include "Memory_kernel.hpp"

namespace ags::are::vk10 {

    void Memory_kernel::init() {
        retrieve_heaps();

        vk::MemoryAllocateInfo allocate_info{
            1024,

        };

        graphics_device.handle.allocateMemory(allocate_info, nullptr);
    }

    void Memory_kernel::term() {

    }

    void Memory_kernel::retrieve_heaps() {
        auto memory_properties = graphics_device.physical_device.getMemoryProperties();
        heaps.resize(memory_properties.memoryHeapCount);
    }

    void* Memory_kernel::map(std::uint64_t n) {

    }

}
