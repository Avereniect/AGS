//
// Created by avereniect on 3/15/22.
//

#ifndef AGS_ARE_VK_MESH_KERNEL_HPP
#define AGS_ARE_VK_MESH_KERNEL_HPP

#include <ags/Graphics_includes.hpp>

#include "Device_kernel.hpp"

namespace ags::are::vk_kernel {

    class Mesh_kernel : public Device_kernel {
    public:

        //=================================================
        // State methods
        //=================================================

        static void init();

        static void term();

    private:

        //=================================================
        // Static members
        //=================================================



    };

}

#endif //AGS_ARE_VK_MESH_KERNEL_HPP
