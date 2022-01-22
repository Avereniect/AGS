//
// Created by avereniect on 1/9/22.
//

#ifndef AGS_DEVICE_KERNEL_HPP
#define AGS_DEVICE_KERNEL_HPP

#include "Kernel_base.hpp"
#include "Device.hpp"

#include <vulkan/vulkan.hpp>

#include <vector>
#include <cstdint>

namespace ags::are::vk10 {

    class Device_kernel : public Kernel_base{
    public:

        static bool init();

        static void term();

    private:

        //=================================================
        // Instance members
        //=================================================

        ///
        /// Device used for rendering.
        ///
        static vk::Device graphics_device;

        ///
        /// Queue used for submitting rendering work.
        ///
        static vk::Queue graphics_work_queue;

        ///
        /// Queue used for submitting compute tasks supporting the rendering
        /// process.
        ///
        static vk::Queue graphics_compute_queue;

        ///
        /// Queue use for submitting transfer tasks supporting the rendering
        /// process.
        ///
        static vk::Queue graphics_transfer_queue;

        ///
        /// A list of all physical devices available.
        ///
        static std::vector<Physical_device> physical_devices;

        //=================================================
        // Helper functions
        //=================================================

        ///
        /// Queries for available physical devices and their properties.
        /// Populates physical_devices and physical_device_properties.
        ///
        static void retrieve_physical_devices();

        ///
        /// Physical devices should have been retrieved before calling this
        /// function
        ///
        /// \return Optimal physical device to use for rendering graphics
        static Physical_device select_graphics_device();

        ///
        /// Create logical device used for rendering graphics and associated
        /// queues.
        ///
        /// \param d Physical device to use as graphics device
        static void create_graphics_device(const Physical_device& d);

        ///
        /// Predicate function used to determine whether a particular device is
        /// suitable for rendering graphics.]
        ///
        /// \param d physical device to check suitability of
        /// \return True if device is suitable to render graphics with
        static bool is_suitable_render_device(const Physical_device& d);

    };

}

#endif //AGS_DEVICE_KERNEL_HPP
