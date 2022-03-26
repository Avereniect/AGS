//
// Created by avereniect on 3/15/22.
//

#ifndef AGS_ARE_VK10_MESH_KERNEL_HPP
#define AGS_ARE_VK10_MESH_KERNEL_HPP

#include "Includes.hpp"
#include "Device_kernel.hpp"

namespace ags::are::vk10 {

    class Mesh_kernel : public Device_kernel {
    public:

        //=================================================
        // State methods
        //=================================================

        void init();

        void term();

    private:

        //=================================================
        // Static members
        //=================================================



    };

}

#endif //AGS_ARE_VK10_MESH_KERNEL_HPP
