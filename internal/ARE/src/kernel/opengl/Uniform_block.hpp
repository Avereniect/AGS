//
// Created by avereniect on 9/4/22.
//

#ifndef AGS_ARE_GL_UNIFORM_BLOCK_HPP
#define AGS_ARE_GL_UNIFORM_BLOCK_HPP

#include "Texture.hpp"

#include "../Uniform_block.hpp"

namespace ags::are::gl_kernel {

    class Uniform_block : public are::Uniform_block {
    public:

        //=================================================
        // -ctors
        //=================================================

        using are::Uniform_block::Uniform_block;

        //=================================================
        // Uniform specification
        //=================================================

        void field(std::string_view str, const Texture1D& tex);
        void field(std::string_view str, const Texture2D& tex);
        void field(std::string_view str, const Texture3D& tex);

        void field(std::string_view str, const aul::Span<Texture1D>);
        void field(std::string_view str, const aul::Span<Texture2D>);

        void field(std::string_view str, const aul::Span<std::reference_wrapper<Texture1D>>);
        void field(std::string_view str, const aul::Span<std::reference_wrapper<Texture2D>>);

        void field(std::string_view str, const aul::Span<Texture1D*>);
        void field(std::string_view str, const aul::Span<Texture2D*>);

    };

}

#endif //AGS_ARE_GL_UNIFORM_BLOCK_HPP
