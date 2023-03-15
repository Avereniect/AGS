#ifndef AGS_ARE_GL_UNIFORM_PACK_HPP
#define AGS_ARE_GL_UNIFORM_PACK_HPP

#include "../Enums_common.hpp"

namespace ags::are::gl_kernel {

    struct Uniform_header {
        Uniform_type type = Uniform_type::NULL_UNIFORM_TYPE;
        std::uint16_t array_size = 0;
    };

    class Uniform_pack {
    public:

        //=================================================
        // -ctors
        //=================================================

        Uniform_pack() = default;
        Uniform_pack(const Uniform_pack&) = delete;
        Uniform_pack(Uniform_pack&&);
        ~Uniform_pack();

        //=================================================
        // Assignment operators
        //=================================================

        Uniform_pack& operator=(const Uniform_pack&) = delete;

        Uniform_pack& operator=(Uniform_pack&&) noexcept;

        //=================================================
        // Mutators
        //=================================================



        //=================================================
        // Accessors
        //=================================================

    private:

        //=================================================
        // Instance members
        //=================================================

        unsigned char* data = nullptr;

        std::uint32_t buffer_size = 0;

    };

}

#endif //AGS_ARE_GL_UNIFORM_PACK_HPP
