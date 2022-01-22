//
// Created by avereniect on 1/12/22.
//

#ifndef AGS_UNIFORM_PACK_HPP
#define AGS_UNIFORM_PACK_HPP

#include "../Enums.hpp"

namespace ags::are::gl33 {

    struct Uniform_header {
        Uniform_type type = Uniform_type::NULL_UNIFORM_TYPE;
        std::uint16_t array_size = 0;
    };

    class Uniform_pack {
    public:

        Uniform_pack() = default;
        ~Uniform_pack();

    private:

        unsigned char* data = nullptr;
        std::uint32_t buffer_size = 0;

    };

}

#endif //AGS_UNIFORM_PACK_HPP
