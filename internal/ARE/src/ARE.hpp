//
// Created by avereniect on 12/17/21.
//

#ifndef AGS_ARE_ARE_HPP
#define AGS_ARE_ARE_HPP

#include <cstdint>
#include <memory>

#ifdef AGS_VULKAN10
#include "kernel/vulkan/Kernel.hpp"
#endif

namespace ags::are {

    class ARE {
    public:

        ///
        /// \param api Enum indicating which API ARE should use
        /// \return True if ARE was initialized successfully. False otherwise
        static bool init();

        ///
        /// Terminates ARE. All resources are freed.
        ///
        static void term();

    private:

        //=================================================
        // Static members
        //=================================================

        static bool is_initialized;

    };

    #ifdef AGS_VULKAN10
    using Kernel = ags::are::vk10::Kernel;
    #endif

}

#endif //AGS_ARE_ARE_HPP
