//
// Created by avereniect on 12/11/21.
//
#ifndef AGS_UI_WINDOW_HPP
#define AGS_UI_WINDOW_HPP

#include <vulkan/vulkan.hpp>
//#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>
#include <cstdint>
#include <string>

namespace ags::ui {

    class Window {
    public:

        //=================================================
        // Helper classes
        //=================================================

        struct vulkan_data;

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

        void move(std::uint32_t x, std::uint32_t y);

        void show();

        void hide();

        void refresh();

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

        #if defined(AGS_VULKAN10)

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

        void create_swapchain(std::uint32_t x, std::uint32_t y);

        //=================================================
        // Callbacks
        //=================================================

        static void mouse_button_callback(GLFWwindow* w, int button, int action, int mods);

        static void mouse_motion_callback(GLFWwindow* w, double xpos, double ypos);

        static void mouse_scroll_callback(GLFWwindow* w, double dx, double dy);


    };

}

#endif //AGS_UI_WINDOW_HPP
