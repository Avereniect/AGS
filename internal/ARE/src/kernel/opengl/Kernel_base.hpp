//
// Created by avereniect on 4/30/22.
//

#ifndef AGS_ARE_KERNEL_BASE_HPP
#define AGS_ARE_KERNEL_BASE_HPP

#include <ags/Graphics_includes.hpp>

#include <aul/Span.hpp>

#include <vector>
#include <string>
#include <string_view>

namespace ags::are::gl_kernel {

    ///
    ///
    ///
    class Kernel_base {
    public:

        //=================================================
        // State functions
        //=================================================

        ///
        /// Initialize OpenGL ARE rendering kernel
        ///
        static void init();

        ///
        /// Terminate OpenGL ARE rendering kernel
        ///
        static void term();

        //=================================================
        // State mutators
        //=================================================

        //=================================================
        // Misc.
        //=================================================

        ///
        ///Query for OpenGL errors and print them to stderr
        ///
        static void poll_errors();

        ///
        /// \return Span over list of supported extensions
        static aul::Span<std::string_view> extensions();

        ///
        /// \return True if extension by specified name is supported by current
        /// platform. False otherwise
        static bool check_extension_support(std::string_view);

        //=================================================
        // Accessors
        //=================================================

        ///
        /// Copy of pointer to GLFWwindow associated with the OpenGL context
        /// that is used for rendering.
        ///
        /// \return
        [[nodiscard]]
        static GLFWwindow* native_context_handle();

    private:

        //=================================================
        // Static members
        //=================================================

        ///
        /// Handle to GLFW window associated with native_context_handle that will be used for
        /// rendering.
        ///
        static GLFWwindow* render_context;

        ///
        /// A list of extensions supported by the current OpenGL implementation.
        ///
        ///
        static std::vector<std::string_view> extensions_list;

        //=================================================
        // Helper functions
        //=================================================

        ///
        /// \param error OpenGL error enum
        /// \return String representation of error
        static std::string_view error_to_string(GLenum error);

        ///
        /// \param error_source OpenGL error source enum
        /// \return String representation of error source
        static std::string_view error_source_to_string(GLenum error_source);

        ///
        /// \param error_type OpenGL error type enum
        /// \return String representation of error type
        static std::string_view error_type_to_string(GLenum error_type);

        ///
        /// \param error_type OpenGL error severity enum
        /// \return String representation of error type
        static std::string_view error_severity_to_string(GLenum error_severity);

        //=================================================
        // Callbacks
        //=================================================

        ///
        /// Callback passed to OpenGL's debug printing system.
        ///
        static void APIENTRY debug_callback(
            GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* user_param
        );

    };

}

#endif //AGS_ARE_KERNEL_BASE_HPP
