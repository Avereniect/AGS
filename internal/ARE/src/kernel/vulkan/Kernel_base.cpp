//
// Created by avereniect on 1/13/22.
//
#include "Kernel_base.hpp"

#include <cstdint>

namespace ags::are::vk10 {

    VkInstance Kernel_base::instance{};

    bool Kernel_base::init() {
        return true;
    }

    void Kernel_base::term() {

    }

}