//
// Created by avereniect on 8/17/22.
//
#include "Sampler.hpp"

namespace ags::are::gl_kernel {

    //=====================================================
    // -ctors
    //=====================================================

    Sampler::Sampler(
        Texture_wrap wrap,
        Texture_filter tex_min_filter,
        Texture_filter tex_mag_filter,
        Mipmap_filter mip_filter
    ):
        tex_wrap(wrap),
        tex_min_filter(tex_min_filter),
        tex_mag_filter(tex_mag_filter),
        mip_filter(mip_filter) {

        glGenSamplers(1, &id);

        auto tmp0 = to_native_enum(wrap);
        glSamplerParameteri(id, GL_TEXTURE_WRAP_R, tmp0);
        glSamplerParameteri(id, GL_TEXTURE_WRAP_S, tmp0);
        glSamplerParameteri(id, GL_TEXTURE_WRAP_T, tmp0);

        auto tmp1 = to_native_enum(tex_min_filter, mip_filter);
        glSamplerParameteri(id, GL_TEXTURE_MIN_FILTER, tmp1);

        auto tmp2 = to_native_enum(tex_mag_filter);
        glSamplerParameteri(id, GL_TEXTURE_MAG_FILTER, tmp2);
    }

    Sampler::Sampler(Sampler&& sampler) noexcept:
        tex_wrap(sampler.tex_wrap),
        tex_min_filter(sampler.tex_min_filter),
        tex_mag_filter(sampler.tex_mag_filter),
        mip_filter(sampler.mip_filter) {

        tex_wrap = Texture_wrap::NULL_WRAP;
        tex_min_filter = Texture_filter::NULL_FILTER;
        tex_mag_filter = Texture_filter::NULL_FILTER;
        mip_filter = Mipmap_filter::NULL_MIPMAP_FILTER;
    }

    Sampler::Sampler() noexcept:
        tex_wrap(),
        tex_min_filter(),
        tex_mag_filter(),
        mip_filter() {}

    Sampler::~Sampler() {
        glDeleteSamplers(1, &id);
    }

    //=====================================================
    // Assignment operators
    //=====================================================

    Sampler& Sampler::operator=(Sampler&& rhs) noexcept {
        tex_wrap = rhs.tex_wrap;
        tex_min_filter = rhs.tex_min_filter;
        tex_mag_filter = rhs.tex_mag_filter;
        mip_filter = rhs.mip_filter;

        tex_wrap = Texture_wrap::NULL_WRAP;
        tex_min_filter = Texture_filter::NULL_FILTER;
        tex_mag_filter = Texture_filter::NULL_FILTER;
        mip_filter = Mipmap_filter::NULL_MIPMAP_FILTER;

        return *this;
    }

    //=====================================================
    // Accessors
    //=====================================================

    Texture_wrap Sampler::texture_wrap() const {
        return tex_wrap;
    }

    Texture_filter Sampler::texture_min_filter() const {
        return tex_min_filter;
    }

    Texture_filter Sampler::texture_mag_filter() const {
        return tex_mag_filter;
    }

    Mipmap_filter Sampler::mipmap_filter() const {
        return mip_filter;
    }

}