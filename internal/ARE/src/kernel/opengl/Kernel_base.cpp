//
// Created by avereniect on 4/30/22.
//
#include "Kernel_base.hpp"

#include <ags/Logging.hpp>

#include <aul/Algorithms.hpp>

#include <iostream>
#include <algorithm>

namespace ags::are::gl_kernel {

    //=================================================
    // Static members
    //=================================================

    std::vector<std::string_view> Kernel_base::extensions_list{};

    GLFWwindow* Kernel_base::render_context = nullptr;

    //=================================================
    // State mutators
    //=================================================

    void Kernel_base::init() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        render_context = glfwCreateWindow(800, 600, "render native_context_handle", nullptr, nullptr);
        if (!render_context) {
            AGS_FATAL("{}", "Failed to create render native_context_handle");
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(render_context);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            AGS_FATAL("{}", "Failed to initialize GLAD");
            exit(EXIT_FAILURE);
        }


        //TODO: Make this dependent on debug macro
        //Set up debugging
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(Kernel_base::debug_callback, nullptr);


        //Retrieve available extensions
        int extension_count;
        glGetIntegerv(GL_NUM_EXTENSIONS, &extension_count);
        for(GLsizei i = 0; i < extension_count; i++) {
            const GLubyte *ptr = glGetStringi(GL_EXTENSIONS, i);
            extensions_list.emplace_back(reinterpret_cast<const char*>(ptr));
        }

        std::sort(extensions_list.begin(), extensions_list.end());
    }

    void Kernel_base::term() {

    }

    //=================================================
    // State mutators
    //=================================================

    //=================================================
    // Misc.
    //=================================================

    void Kernel_base::poll_errors() {
        for (auto error = glGetError(); error != GL_NO_ERROR; error = glGetError()) {
            AGS_ERROR(
                "OpenGL error code {}: {}",
                error,
                error_to_string(error)
            );

            int break_point_dummy = 1;
        }
    }

    aul::Span<std::string_view> Kernel_base::extensions() {
        return {extensions_list.begin(), extensions_list.end()};
    }

    bool Kernel_base::check_extension_support(std::string_view view) {
        auto it = aul::binary_search(extensions_list.begin(), extensions_list.end(), view);
        return (it != extensions_list.end());
    }

    //=================================================
    // Accessors
    //=================================================

    GLFWwindow* Kernel_base::native_context_handle() {
        return render_context;
    }

    //=================================================
    // Helper functions
    //=================================================

    std::string_view Kernel_base::error_to_string(GLenum error) {
        switch (error) {
        case GL_INVALID_OPERATION:
            return {"GL_INVALID_OPERATION"};
        case GL_INVALID_ENUM:
            return {"GL_INVALID_ENUM"};
        case GL_INVALID_VALUE:
            return {"GL_INVALID_VALUE"};
        case GL_STACK_OVERFLOW:
            return {"GL_STACK_OVERFLOW"};
        case GL_STACK_UNDERFLOW:
            return {"GL_STACK_UNDERFLOW"};
        case GL_OUT_OF_MEMORY:
            return {"GL_OUT_OF_MEMORY"};
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return {"GL_INVALID_FRAMEBUFFER_OPERATION"};
        case GL_CONTEXT_LOST:
            return {"GL_CONTEXT_LOST"};
        default:
            return {"Unrecognized error enum"};
        }
    }

    std::string_view Kernel_base::error_source_to_string(GLenum error_source) {
        switch (error_source) {
        case GL_DEBUG_SOURCE_API:
            return {"GL_DEBUG_SOURCE_API"};
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return {"GL_DEBUG_SOURCE_WINDOW_SYSTEM"};
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return {"GL_DEBUG_SOURCE_SHADER_COMPILER"};
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            return {"GL_DEBUG_SOURCE_THIRD_PARTY"};
        case GL_DEBUG_SOURCE_APPLICATION:
            return {"GL_DEBUG_SOURCE_APPLICATION"};
        case GL_DEBUG_SOURCE_OTHER:
            return {"GL_DEBUG_SOURCE_OTHER"};
        default:
            return {"Unrecognized error source enum"};
        }
    }

    std::string_view Kernel_base::error_type_to_string(GLenum error_type) {
        switch (error_type) {
        case GL_DEBUG_TYPE_ERROR:
            return {"GL_DEBUG_TYPE_ERROR (generic error)"};
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return {"GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR"};
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return {"GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR"};
        case GL_DEBUG_TYPE_PORTABILITY:
            return {"GL_DEBUG_TYPE_PORTABILITY"};
        case GL_DEBUG_TYPE_PERFORMANCE:
            return {"GL_DEBUG_TYPE_PERFORMANCE"};
        case GL_DEBUG_TYPE_MARKER:
            return {"GL_DEBUG_TYPE_MARKER"};
        case GL_DEBUG_TYPE_PUSH_GROUP:
            return {"GL_DEBUG_TYPE_PUSH_GROUP"};
        case GL_DEBUG_TYPE_POP_GROUP:
            return {"GL_DEBUG_TYPE_POP_GROUP"};
        case GL_DEBUG_TYPE_OTHER:
            return {"GL_DEBUG_TYPE_OTHER"};
        default:
            return {"Unrecognized error type enum"};
        }
    }

    std::string_view Kernel_base::error_severity_to_string(GLenum error_severity) {
        switch (error_severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            return {"GL_DEBUG_SEVERITY_HIGH"};
        case GL_DEBUG_SEVERITY_MEDIUM:
            return {"GL_DEBUG_SEVERITY_MEDIUM"};
        case GL_DEBUG_SEVERITY_LOW:
            return {"GL_DEBUG_SEVERITY_LOW"};
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            return {"GL_DEBUG_SEVERITY_NOTIFICATION"};
        default:
            return {"Unrecognized error severity enum"};
        }
    }

    //=================================================
    // Callbacks
    //=================================================

    void Kernel_base::debug_callback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* user_param
    ) {
        std::string error_message;
        error_message.reserve(1024);
        error_message.append("Type: ");
        error_message.append(error_type_to_string(type));
        error_message.append("\nSource:");
        error_message.append(error_source_to_string(source));
        error_message.append("\nMessage::");
        error_message.append(message, length);

        switch (severity) {
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            AGS_NOTIFY("{}", error_message);
            break;
        case GL_DEBUG_SEVERITY_LOW:
            AGS_WARN("{}", error_message);
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            AGS_ERROR("{}", error_message);
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            AGS_ERROR("{}", error_message);
            break;
        default:
            AGS_NOTIFY("Unrecognized error severity.\n{}", error_message);
        }

        int break_point_dummy = 5;
    }

}
