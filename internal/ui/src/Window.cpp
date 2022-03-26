//
// Created by avereniect on 12/11/21.
//

#include "Window.hpp"

#include <ags/ARE.hpp>

#include <ags/Window_core.hpp>

#include <aul/Math.hpp>

#include <vulkan/vulkan.hpp>

#include <utility>
#include <iostream>

namespace ags::ui {

    //=====================================================
    // -ctors
    //=====================================================

    Window::Window(std::uint32_t x, std::uint32_t y, const std::string& title) {
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

        #ifdef AGS_VULKAN10
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        #else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        #endif

        handle = glfwCreateWindow(x, y, title.c_str(), nullptr, nullptr);

        if (!handle) {
            throw std::runtime_error("Failed to create window.");
        }

        glfwSetMouseButtonCallback(handle, Window::mouse_button_callback);
        glfwSetCursorPosCallback(handle, Window::mouse_motion_callback);
        glfwSetScrollCallback(handle, Window::mouse_scroll_callback);

        #ifdef AGS_VULKAN10

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
    }

    Window::Window(Window&& window) noexcept:
        handle(std::exchange(window.handle, nullptr)),
        dims(std::exchange(window.dims, {0, 0})) {}

    Window::~Window() {
        #ifdef AGS_VULKAN10
        for (auto view : swapchain_image_views) {
            are::Kernel::get_graphics_device().handle.destroyImageView(view);
        }

        vkDestroySurfaceKHR(are::Kernel::get_instance(), surface, nullptr);
        #endif

        glfwDestroyWindow(handle);
    }

    Window::Window(std::uint32_t x, std::uint32_t y):
        Window(x, y, "AGS") {}

    //=====================================================
    // Assignment operators
    //=====================================================

    Window& Window::operator=(Window&& win) noexcept {
        handle = std::exchange(win.handle, nullptr);
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
        #ifdef AGS_OPENGL43

        #endif

        #ifdef AGS_VULKAN10
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

    void Window::refresh() {
        //TODO: Use swapchian

        //glfwSwapBuffers(handle);
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
            std::cerr << "Failed to create GLFW window." << std::endl;
        }

        return tmp;
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

}
