//
// Created by avereniect on 12/11/21.
//
#ifndef AGS_UI_WINDOW_HPP
#define AGS_UI_WINDOW_HPP

#include <ags/Graphics_includes.hpp>

#include <array>
#include <cstdint>
#include <string>

#include <ags/ARE.hpp>

namespace ags::ui {

    class Window {
    public:

        //=================================================
        // -ctors
        //=================================================

        ///
        /// \param x Window width
        /// \param y Window height
        Window(std::uint32_t x, std::uint32_t y);

        ///
        /// \param x Window width
        /// \param y Window height
        /// \param title Window title
        Window(std::uint32_t x, std::uint32_t y, const std::string& title);

        Window() = default;
        Window(const Window& window) = delete;
        Window(Window&& window) noexcept;
        ~Window();

        //=================================================
        // Assignment operators
        //=================================================

        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) noexcept;

        //=================================================
        // Mutators
        //=================================================

        ///
        /// Minimize window to taskbar
        ///
        void minimize();

        ///
        /// Maximize window size
        ///
        void maximize();

        ///
        /// \param x Window width to resize to
        /// \param y Window height to resize to
        void resize(std::uint32_t x, std::uint32_t y);

        ///
        /// Relocate window to be at specified coordinates at monitor
        ///
        /// \param x X coordinate in monitor
        /// \param y Y coordinate in
        void move(std::uint32_t x, std::uint32_t y);

        ///
        /// Show the window.
        ///
        void show();

        ///
        /// Hide the window.
        ///
        void hide();

        ///
        /// Display the contents of the of the texture on the window.
        ///
        /// If the texture is of a lower resolution than the window, then it
        /// will be centered with a black border around it.
        ///
        /// If the texture is of a higher resolution than the window, then it
        /// will be centered, with the contents that lie outside the bounds of
        /// the windows cut off.
        ///
        /// \param texture Texture to display on  window
        void refresh(const ags::are::Texture2D& texture);

        void refresh(const ags::are::Framebuffer& framebuffer, std::uint32_t attachment = 0);

        //=================================================
        // Accessors
        //=================================================

        ///
        ///
        /// \return True if window should close. False otherwise
        [[nodiscard]]
        bool should_close() const;

        ///
        /// \return Tuple containing window (width, height).
        [[nodiscard]]
        std::array<std::uint32_t, 2> dimensions() const;

        ///
        /// \return Window width
        [[nodiscard]]
        std::uint32_t width() const;

        ///
        /// \return Window height
        [[nodiscard]]
        std::uint32_t height() const;

        //=================================================
        // Conversion operators
        //=================================================

        ///
        /// \return True if object holds a window resource. False otherwise
        operator bool() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        ///
        /// Window handle
        ///
        GLFWwindow* handle = nullptr;

        ///
        /// (w, h) dimensions of window
        ///
        std::array<std::uint32_t, 2> dims{0, 0};

        ///
        /// (w, h) dimensions of window frame
        ///
        std::array<std::uint32_t, 2> frame_dims{0, 0};

        #if defined(AGS_OPENGL)

        ///
        /// Dummy VAO
        ///
        /// Exists only to satisfy the VAO requirement imposed by the OpenGL
        /// core profile
        ///
        static GLuint display_vao;

        static GLuint display_vertex_shader;
        static GLuint display_fragment_shader;
        static GLuint display_shader_program;

        #endif

        #if defined(AGS_VULKAN)

        vk::SurfaceKHR surface{};

        VkSurfaceCapabilitiesKHR surface_capabilities{};

        vk::SwapchainKHR swapchain{};

        std::uint32_t swapchain_image_count;

        std::vector<vk::Image> swapchain_images;
        std::vector<vk::ImageView> swapchain_image_views;

        #endif

        //=================================================
        // Helper functions
        //=================================================

        ///
        /// \param x Window width
        /// \param y Window height
        /// \return Pointer to newly created GLFWwindow object
        static GLFWwindow* create_handle(std::uint32_t x, std::uint32_t y, const std::string&);

        ///
        /// Native OpenGL rendering context should be active in current thread
        /// before calling
        ///
        static void setup_display_shader();

        //=================================================
        // Callbacks
        //=================================================

        static void mouse_button_callback(GLFWwindow* w, int button, int action, int mods);

        static void mouse_motion_callback(GLFWwindow* w, double xpos, double ypos);

        static void mouse_scroll_callback(GLFWwindow* w, double dx, double dy);

        static void window_size_callback(GLFWwindow* w, int width, int height);

    };

}

#endif //AGS_UI_WINDOW_HPP
