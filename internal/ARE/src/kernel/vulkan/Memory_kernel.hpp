//
// Created by avereniect on 3/16/22.
//

#ifndef AGS_ARE_VK_MEMORY_KERNEL_HPP
#define AGS_ARE_VK_MEMORY_KERNEL_HPP

#include <ags/Graphics_includes.hpp>

#include "Device_kernel.hpp"

#include <cstdint>

namespace ags::are::vk_kernel {

    enum class Heap_type : std::uint8_t {
        NULL_HEAP_TYPE,
        DEVICE_MEMORY, //Dedicated GPU's VRAM
        HOST_MEMORY, //System RAM
        SHARED_MEMORY, //Integrated GPU's RAM/system RAM
        TRANSFER_MEMORY //Dedicated GPU's RAM specialized for memory transfers
    };

    ///
    /// Enum representing the access patterns for the buffer
    ///
    /// STATIC denotes a buffer whose contents are not updated frequently.
    /// DYNAMIC denotes a buffer whose contents are updated very frequently.
    ///
    enum class Buffer_usage : std::uint8_t {
        NULL_USAGE,
        STATIC,
        DYNAMIC
    };

    struct Heap {
        Heap_type type = Heap_type::NULL_HEAP_TYPE;
        std::uint64_t size = 0;
    };

    class Memory_kernel : public Device_kernel {
    public:

        //=================================================
        // State methods
        //=================================================

        ///
        /// Initialize memory kernel
        ///
        void init();

        ///
        /// Terminate memory kernel
        ///
        void term();

        //=================================================
        // Buffer Allocation methods
        //=================================================

        ///
        /// \param size Buffer size
        /// \param usage Enum describing buffer usage
        /// \return newly created vk::Buffer
        static vk::Buffer create_vertex_buffer(std::uint32_t size, Buffer_usage usage = {});

        ///
        /// \param size Buffer size
        /// \param usage Enum describing buffer usage
        static void load_vertex_buffer(vk::Buffer buffer, std::uint32_t*, std::uint32_t size);

        ///
        /// \param size Buffer size
        /// \param usage Enum describing buffer usage
        /// \return
        static vk::Buffer create_index_buffer(std::uint32_t size, Buffer_usage usage = {});

        ///
        /// \param size Buffer size
        /// \param usage Enum describing buffer usage
        /// \return
        static vk::Buffer create_image_buffer(std::uint32_t size, Buffer_usage usage = {});

    protected:

        //=================================================
        // Static state
        //=================================================

        ///
        /// List of memory heaps available to the graphics device
        ///
        static std::vector<Heap> heaps;

        ///
        /// List of heaps in order of suitability for static allocations
        ///
        static std::vector<std::reference_wrapper<Heap>> static_heaps;

        ///
        /// List of heaps in order of suitability for dynamic allocations
        ///
        static std::vector<std::reference_wrapper<Heap>> dynamic_heaps;

        //=================================================
        // Helper functions
        //=================================================

        static void retrieve_heaps();

        ///
        /// Allocates a Vulkan buffer
        ///
        /// \return
        static vk::Buffer create_buffer_exclusive(std::uint32_t);

    };

}

#endif //AGS_ARE_VK_MEMORY_KERNEL_HPP
