//
// Created by avereniect on 1/9/22.
//

#ifndef AGS_ARE_VK10_DEVICE_KERNEL_HPP
#define AGS_ARE_VK10_DEVICE_KERNEL_HPP

#include "Includes.hpp"

#include "Kernel_base.hpp"
#include "Device.hpp"

#include <cstdint>
#include <array>
#include <vector>

namespace ags::are::vk10 {

    class Device_kernel : public Kernel_base {
    public:

        //=================================================
        // State methods
        //=================================================

        static bool init();
        static void term();

        //=================================================
        // Accessors
        //=================================================

        static const Graphics_device& get_graphics_device();

        static const Compute_device& get_heavy_compute_device();

        static const Compute_device& get_light_compute_device();

    protected:

        //=================================================
        // Instance members
        //=================================================

        ///
        /// Device which is used for the purpose of rendering and presenting
        /// graphics.
        ///
        static Graphics_device graphics_device;

        ///
        /// Device which is used for performing heavy computational tasks
        ///
        static Compute_device heavy_compute_device;

        ///
        /// Device which is used for performing light computational tasks
        ///
        static Compute_device light_compute_device;

        ///
        /// A list of all physical devices available.
        ///
        static std::vector<Physical_device> physical_devices;

        ///
        /// List of device extensions required by graphics device
        ///
        static constexpr std::array<const char*, 1> graphics_device_extensions {
            "VK_KHR_swapchain"
        };

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
        /// \return Optimal physical device to use for heavy general-purpose
        /// compute tasks
        static Physical_device select_heavy_compute_device();

        ///
        /// \return Optimal physical device to use for light general-purpose
        /// compute tasks
        static Physical_device select_light_compute_device();

        ///
        /// Create logical device used for rendering graphics and associated
        /// queues.
        ///
        /// \param d Physical device to use as graphics device
        static void create_graphics_device(const Physical_device& d);

        ///
        /// Create logical device used for heavy general-purpose compute tasks.
        ///
        /// \param d Physical device to use as heavy compute device
        static void create_heavy_compute_device(const Physical_device& d);

        ///
        /// Create logical device used for light general-purpose compute tasks.
        ///
        /// \param d PHysical device to use as a light compute device
        static void create_light_compute_device(const Physical_device& d);

        ///
        /// Predicate function used to determine whether a particular device is
        /// suitable for rendering graphics.
        ///
        /// \param d physical device to check suitability of
        /// \return True if device is suitable to render graphics with
        static bool is_suitable_graphics_device(const Physical_device& d);

        ///
        /// Predicate function used to determine whether a particular device is
        /// suitable for use as a heavy compute device
        ///
        /// \param d Physical device to check suitability of
        /// \return True if device is suitable for use as a heavy compute device
        static bool is_suitable_heavy_compute_device(const Physical_device& d);

        ///
        /// Predicate function used to determine whether a particular device is
        /// suitable for use as a light compute device
        ///
        /// \param d Physical device to check suitability of
        /// \return True if device is suitable for use as a light compute device
        static bool is_suitable_light_compute_device(const Physical_device& d);

    };

}

#endif //AGS_ARE_VK10_DEVICE_KERNEL_HPP
