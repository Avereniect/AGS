//
// Created by avereniect on 12/17/21.
//

#ifndef AGS_ARE_ARE_HPP
#define AGS_ARE_ARE_HPP

#include <cstdint>
#include <memory>

#include "kernel/vulkan/Kernel.hpp"

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

}

#endif //AGS_ARE_ARE_HPP
