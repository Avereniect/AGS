//
// Created by avereniect on 3/15/22.
//
#include "Mesh_kernel.hpp"

#include "Device_kernel.hpp"

namespace ags::are::vk10 {

    void Mesh_kernel::init() {
        auto memory_properties = graphics_device.physical_device.getMemoryProperties();
        memory_properties.memoryHeaps;

    }

    void Mesh_kernel::term() {

    }

}
