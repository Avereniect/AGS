//
// Created by avereniect on 8/17/22.
//

#ifndef AGS_SAMPLER_HPP
#define AGS_SAMPLER_HPP

#include "Object.hpp"

#include "Enums.hpp"

namespace ags::are::gl_kernel {

    class alignas(8) Sampler : public Object {
    public:

        //=================================================
        // -ctors
        //=================================================

        ///
        /// \param wrap
        /// \param tex_mag_filter
        /// \param tex_min_filter
        /// \param mip_filter
        Sampler(
            Texture_wrap wrap,
            Texture_filter tex_mag_filter,
            Texture_filter tex_min_filter,
            Mipmap_filter mip_filter
        );

        Sampler() noexcept;
        Sampler(const Sampler&) = delete;
        Sampler(Sampler&&) noexcept;
        ~Sampler();

        //=================================================
        // Assignment operators
        //=================================================

        Sampler& operator=(const Sampler&) = delete;

        Sampler& operator=(Sampler&&) noexcept;

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        Texture_wrap texture_wrap() const;

        [[nodiscard]]
        Texture_filter texture_min_filter() const;

        [[nodiscard]]
        Texture_filter texture_mag_filter() const;

        [[nodiscard]]
        Mipmap_filter mipmap_filter() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        Texture_wrap tex_wrap : 2;

        Texture_filter tex_min_filter : 2;

        Texture_filter tex_mag_filter : 2;

        Mipmap_filter mip_filter : 2;

    };

}

#endif //AGS_SAMPLER_HPP
