//
// Created by avereniect on 3/16/22.
//

#ifndef AGS_ARE_VK10_MEMORY_KERNEL_HPP
#define AGS_ARE_VK10_MEMORY_KERNEL_HPP

#include "Includes.hpp"
#include "Device_kernel.hpp"

#include <cstdint>

namespace ags::are::vk10 {

    enum class Heap_type :std::uint8_t {
        NULL_HEAP_TYPE,
        DEVICE_MEMORY, //Dedicated GPU's VRAM
        HOST_MEMORY, //System RAM
        SHARED_MEMORY, //Integrated GPU's RAM/system RAM
        TRANSFER_MEMORY //Dedicated GPU's RAM specialized for memory transfers
    };

    struct Heap {
        Heap_type type = Heap_type::NULL_HEAP_TYPE;
        std::uint64_t size = 0x00;
    };

    class Memory_kernel : public Device_kernel {
    public:

        //=================================================
        // State methods
        //=================================================

        ///
        ///
        ///
        void init();

        ///
        ///
        ///
        void term();

        ///
        ///
        ///
        void transfer_memory();

        ///
        /// \param n
        /// \return
        void* map(std::uint64_t n);

        ///
        ///
        /// \param ptr
        void unmap(void* ptr);

    protected:

        //=================================================
        // Static state
        //=================================================

        static std::vector<Heap> heaps;

        //=================================================
        // Helper functions
        //=================================================

        static void retrieve_heaps();

    };

}

#endif //AGS_ARE_VK10_MEMORY_KERNEL_HPP
