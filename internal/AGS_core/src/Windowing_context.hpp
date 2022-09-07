//
// Created by avereniect on 1/18/22.
//

#ifndef AGS_CORE_WINDOWING_CONTEXT_HPP
#define AGS_CORE_WINDOWING_CONTEXT_HPP

namespace ags {

    ///
    /// Class managing GLFW windowing library.
    ///
    /// Must be initialized before usage of windows from ui module
    ///
    class Windowing_context {
    public:

        ///
        /// Initialize GLFW library.
        ///
        /// Sets up error callback
        ///
        static void init();

        ///
        /// Terminate GLFW library.
        ///
        static void term();

        ///
        /// Query OS for input events
        ///
        static void poll_events();

    private:

        static void error_callback(int error_code, const char* message);

    };

}

#endif //AGS_CORE_WINDOWING_CONTEXT_HPP
