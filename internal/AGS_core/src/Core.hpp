//
// Created by avereniect on 1/18/22.
//

#ifndef AGS_CORE_CORE_HPP
#define AGS_CORE_CORE_HPP

#ifdef AGS_VULKAN10
#include "Vulkan_context.hpp"
#endif

namespace ags {

    ///
    /// Wrapper class around various libraries that need to be initialized before
    /// use by the application.
    ///
    class Core {
    public:

        static void init();
        static void term();

    private:

        static bool is_initialized;

    };

}

#endif //AGS_CORE_CORE_HPP
