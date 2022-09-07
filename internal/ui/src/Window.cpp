//
// Created by avereniect on 12/11/21.
//

#include "Window.hpp"

#include <ags/Util.hpp>
#include <ags/Logging.hpp>
#include <ags/ARE.hpp>

#include <aul/Math.hpp>

#include <vulkan/vulkan.hpp>

#include <utility>
#include <iostream>

namespace ags::ui {

    //=====================================================
    // Static members
    //=====================================================

    GLuint Window::display_vao = 0;

    GLuint Window::display_vertex_shader = 0;
    GLuint Window::display_fragment_shader = 0;
    GLuint Window::display_shader_program = 0;

    //=====================================================
    // -ctors
    //=====================================================

    Window::Window(std::uint32_t x, std::uint32_t y, const std::string& title) {
        #if defined(AGS_VULKAN)
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        handle = glfwCreateWindow(x, y, title.c_str(), nullptr, nullptr);

        #elif defined(AGS_OPENGL)
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

        handle = glfwCreateWindow(
            x, y,
            title.c_str(),
            nullptr,
            ags::are::Kernel::Kernel::native_context_handle()
        );

        #else
        static_assert(false, "No graphics API selected");
        #endif

        if (!handle) {
            AGS_FATAL("{}", "Failed to create GLFW window");
            exit(EXIT_FAILURE);
        }

        glfwSetMouseButtonCallback(handle, Window::mouse_button_callback);
        glfwSetCursorPosCallback(handle, Window::mouse_motion_callback);
        glfwSetScrollCallback(handle, Window::mouse_scroll_callback);

        dims = {x, y};
        int tmp_frame_dims[2];
        glfwGetFramebufferSize(handle, tmp_frame_dims + 0, tmp_frame_dims + 1);
        this->frame_dims[0] = tmp_frame_dims[0];
        this->frame_dims[1] = tmp_frame_dims[1];

        #ifdef AGS_VULKAN

        VkSurfaceKHR surface_tmp;
        VkResult result = glfwCreateWindowSurface(
            are::Kernel::get_instance(),
            handle,
            nullptr,
            &surface_tmp
        );

        surface = surface_tmp;

        if (result != VK_SUCCESS) {
            std::cerr << "Failed to create window surface" << std::endl;
        }

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
            are::Kernel::get_graphics_device().physical_device,//Vulkan_context::graphics_device.physical_device,
            surface,
            &surface_capabilities
        );

        swapchain_image_count = std::min(
            surface_capabilities.minImageCount + 1,
            surface_capabilities.maxImageCount
        );

        #endif

        #if defined(AGS_OPENGL)
        glfwMakeContextCurrent(handle);

        //Set up dummy vao
        glGenVertexArrays(1, &display_vao);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glfwMakeContextCurrent(are::Kernel::native_context_handle());

        //Set up display shader
        setup_display_shader();
        #endif
    }

    Window::Window(Window&& window) noexcept:
        handle(std::exchange(window.handle, nullptr)),
        dims(std::exchange(window.dims, {0, 0})),
        frame_dims(std::exchange(window.frame_dims, {0, 0})) {}

    Window::~Window() {
        #ifdef AGS_VULKAN
        for (auto view : swapchain_image_views) {
            are::Kernel::get_graphics_device().handle.destroyImageView(view);
        }

        vkDestroySurfaceKHR(are::Kernel::get_instance(), surface, nullptr);
        #endif

        glfwMakeContextCurrent(handle);
        glDeleteVertexArrays(1, &display_vao);

        glfwDestroyWindow(handle);
    }

    Window::Window(std::uint32_t x, std::uint32_t y):
        Window(x, y, "AGS") {}

    //=====================================================
    // Assignment operators
    //=====================================================

    Window& Window::operator=(Window&& win) noexcept {
        handle = std::exchange(win.handle, nullptr);
        dims = std::exchange(win.dims, {0, 0});
        frame_dims = std::exchange(win.frame_dims, {0, 0});
        return *this;
    }

    //=====================================================
    // Mutators
    //=====================================================

    void Window::minimize() {
        glfwIconifyWindow(handle);
    }

    void Window::maximize() {
        glfwMaximizeWindow(handle);
    }

    void Window::resize(std::uint32_t x, std::uint32_t y) {
        #ifdef AGS_OPENGL
        dims = {x, y};
        #endif

        #ifdef AGS_VULKAN
        auto max_extent = surface_capabilities.maxImageExtent;
        auto min_extent = surface_capabilities.minImageExtent;

        x = aul::clamp(x, min_extent.width, max_extent.width);
        y = aul::clamp(y, min_extent.height, min_extent.height);
        #endif

        glfwSetWindowSize(handle, x, y);
    }

    void Window::move(std::uint32_t x, std::uint32_t y) {
        glfwSetWindowPos(handle, x, y);
    }

    void Window::show() {
        glfwShowWindow(handle);
    }

    void Window::hide() {
        glfwHideWindow(handle);
    }

    void Window::refresh(const ags::are::Texture2D& texture) {
        #if defined(AGS_OPENGL)
        glfwMakeContextCurrent(handle);

        glClearColor(0.25f, 0.50f, 0.75f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture.native_handle());

        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0.0f, 0.0f);
            //glColor3f(0.0f, 0.0f, 0.0f);
            glVertex2f(-1.0f, +1.0f);

            glTexCoord2f(0.0f, 2.0f);
            //glColor3f(0.0f, 2.0f, 0.0f);
            glVertex2f(-1.0f, -3.0f);

            glTexCoord2f(2.0f, 0.0f);
            //glColor3f(2.0f, 0.0f, 0.0f);
            glVertex2f(+3.0f, +1.0f);
        glEnd();

        glFlush();
        glFinish();

        glfwSwapBuffers(handle);
        glfwMakeContextCurrent(are::Kernel::native_context_handle());
        glfwPollEvents();
        #endif
    }

    void Window::refresh(const ags::are::Framebuffer& framebuffer, std::uint32_t attachment) {
        #if defined(AGS_OPENGL)
        glfwMakeContextCurrent(handle);
        are::Kernel::poll_errors();

        //TODO: Clean this code up, perhaps cache some of it

        std::uint32_t viewport_width = std::min(framebuffer.width(), frame_dims[0]);
        std::uint32_t viewport_height = std::min(framebuffer.width(), frame_dims[1]);

        //Handle off-by-one errors cause by rounding and flipping vertical coordinates in shader
        std::int32_t v_adjustment = ((framebuffer.height()) ^ (frame_dims[1])) & 0x01;

        std::int32_t viewport_x_offset = std::int32_t((frame_dims[0]) - framebuffer.width() ) / 2;
        std::int32_t viewport_y_offset = std::int32_t((frame_dims[1]) - framebuffer.height()) / 2;

        auto attachment_id = framebuffer.native_color_attachment_handles()[attachment];

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, attachment_id);

        glUseProgram(display_shader_program);

        const GLint viewport_dims_location  = glGetUniformLocation(display_shader_program, "viewport_dims");
        const GLint viewport_offset_location  = glGetUniformLocation(display_shader_program, "viewport_offset");

        const GLint ms_texture_sampler_location = glGetUniformLocation(display_shader_program, "ms_image_sampler");
        const GLint sample_count_uniform_location = glGetUniformLocation(display_shader_program, "sample_count");

        glUniform1i(sample_count_uniform_location, GLint(framebuffer.samples()));
        glUniform1i(ms_texture_sampler_location, 1);
        glUniform2i(viewport_dims_location, frame_dims[0], frame_dims[1]);
        glUniform2i(viewport_offset_location, viewport_x_offset, viewport_y_offset + v_adjustment);

        //TODO: Change this to be black
        glClearColor(0.25f, 0.25f, 0.25f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(
            std::max(viewport_x_offset, 0),
            std::max(viewport_y_offset, 0),
            viewport_width,
            viewport_height
        );

        are::Kernel::poll_errors();
        glBindVertexArray(display_vao);
        are::Kernel::poll_errors();

        glDrawArrays(GL_TRIANGLES, 0, 3);
        are::Kernel::poll_errors();

        glFlush();
        glFinish();

        glfwSwapBuffers(handle);
        glfwMakeContextCurrent(are::Kernel::native_context_handle());
        glfwPollEvents();
        #endif
    }

    //=====================================================
    // Accessors
    //=====================================================

    bool Window::should_close() const {
        return glfwWindowShouldClose(handle);
    }

    std::array<std::uint32_t, 2> Window::dimensions() const {
        return dims;
    }

    std::uint32_t Window::width() const {
        return dims[0];
    }

    std::uint32_t Window::height() const {
        return dims[1];
    }

    //=====================================================
    // Conversion operators
    //=====================================================

    Window::operator bool() const {
        return handle;
    }

    //=====================================================
    // Helper functions
    //=====================================================

    GLFWwindow* Window::create_handle(std::uint32_t x, std::uint32_t y, const std::string& title) {
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

        #ifdef AGS_VULKAN10
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        #else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        #endif

        GLFWwindow* tmp = glfwCreateWindow(x, y, title.c_str(), nullptr, nullptr);

        if (!tmp) {
            AGS_ERROR("{}\n{}", AGS_CODE_LOCATION, "Failed to create GLFW window");
            exit(EXIT_FAILURE);
        }

        return tmp;
    }

    void Window::setup_display_shader() {
        if (display_shader_program) {
            return;
        }

        {
            display_vertex_shader = glCreateShader(GL_VERTEX_SHADER);

            std::string vert_src = ags::read_ascii_text("./assets/shaders/glsl33/display.vs.glsl");
            const char* display_vertex_shader_ptr = vert_src.data();
            auto vert_src_length = static_cast<GLint>(vert_src.size());
            glShaderSource(display_vertex_shader, 1, &display_vertex_shader_ptr, &vert_src_length);
            glCompileShader(display_vertex_shader);

            GLint success;
            glGetShaderiv(display_vertex_shader, GL_COMPILE_STATUS, &success);
            
            if (!success) {
                std::string buffer;
                buffer.resize(4 * 1024);
                glGetShaderInfoLog(display_vertex_shader, buffer.size(), nullptr, buffer.data());
                AGS_ERROR("{}\n{}", "Error when compiling shader program.", buffer.data());
                return;
            }
        }

        {
            display_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            std::string frag_src = ags::read_ascii_text("./assets/shaders/glsl33/display.fs.glsl");
            const char* display_fragment_shader_ptr = frag_src.data();
            auto frag_src_length = static_cast<GLint>(frag_src.size());
            glShaderSource(display_fragment_shader, 1, &display_fragment_shader_ptr, &frag_src_length);
            glCompileShader(display_fragment_shader);

            GLint success;
            glGetShaderiv(display_fragment_shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                std::string buffer;
                buffer.resize(4 * 1024);

                GLsizei length;
                glGetShaderInfoLog(display_fragment_shader, buffer.size(), &length, buffer.data());
                AGS_ERROR("{}\n{}", "Error when compiling shader program.", buffer.data());
                return;
            }
        }

        {
            display_shader_program = glCreateProgram();
            glAttachShader(display_shader_program, display_vertex_shader);
            glAttachShader(display_shader_program, display_fragment_shader);
            glLinkProgram(display_shader_program);

            GLint success;
            glGetProgramiv(display_shader_program, GL_LINK_STATUS, &success);
            if (!success) {
                std::basic_string<GLchar> buffer;
                buffer.resize(4 * 1024);
                glGetShaderInfoLog(display_shader_program, buffer.size(), nullptr, buffer.data());
                AGS_ERROR("{}\n{}", "Error when linking shader program.", buffer.data());
                return;
            }
        }

        glDetachShader(display_shader_program, display_vertex_shader);
        glDetachShader(display_shader_program, display_fragment_shader);

        are::Kernel::poll_errors();
    }

    #ifdef AGS_VULKAN10
    void Window::create_swapchain(std::uint32_t x, std::uint32_t y) {
        using are::vk10::Kernel;
        auto& graphics_device = Kernel::get_graphics_device();

        vk::SwapchainCreateInfoKHR swapchain_create_info{
            vk::SwapchainCreateFlagBitsKHR{},
            surface,
            swapchain_image_count,
            Kernel::get_presentation_format(), //Vulkan_context::surface_format.format,
            Kernel::get_presentation_colorspace(),
            vk::Extent2D{x, y},
            1,
            vk::ImageUsageFlagBits::eColorAttachment,
            vk::SharingMode::eExclusive,
            1,
            &graphics_device.graphics_queue_index,
            vk::SurfaceTransformFlagBitsKHR::eIdentity,
            vk::CompositeAlphaFlagBitsKHR::eOpaque,
            Kernel::get_presentation_mode(), //Vulkan_context::present_mode,
            false,
            swapchain
        };

        //TODO: Handle case where swap chain creation fails
        swapchain = graphics_device.handle.createSwapchainKHR(
            swapchain_create_info
        );

        if (!swapchain) {
            throw std::runtime_error("Failed to create swapchain.");
        }

        swapchain_images = graphics_device.handle.getSwapchainImagesKHR(swapchain);

        swapchain_image_views.reserve(swapchain_images.size());

        vk::ImageSubresourceRange range{
            vk::ImageAspectFlagBits::eColor,
            0,
            1,
            0,
            1
        };

        vk::ImageViewCreateInfo view_create_info{
            {},
            {},
            vk::ImageViewType::e2D, Kernel::get_surface_format().format,
            vk::ComponentSwizzle::eIdentity,
            range
        };

        for (auto image : swapchain_images) {
            view_create_info.image = image;
            swapchain_image_views.push_back(graphics_device.handle.createImageView(view_create_info));
        }

    }
    #endif

    //=====================================================
    // Callback functions
    //=====================================================

    void Window::mouse_button_callback(GLFWwindow* w, int button, int action, int mods) {

    }

    void Window::mouse_motion_callback(GLFWwindow* w, double xpos, double ypos) {

    }

    void Window::mouse_scroll_callback(GLFWwindow* w, double dx, double dy) {

    }

    void window_size_callback(GLFWwindow* w, int width, int height) {
        //TODO: Handle redrawing screen

    }

}
