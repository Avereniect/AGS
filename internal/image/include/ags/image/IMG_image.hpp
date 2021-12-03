//
// Created by avereniect on 11/27/21.
//

#ifndef AGS_IMG_IMAGE_HPP
#define AGS_IMG_IMAGE_HPP

#include <array>
#include <cstdint>

#include "aul/Bits.hpp"
#include "aul/Utility.hpp"

namespace ags {

    ///
    /// Byte alignment of allocations made by owning image classes
    ///
    /// 512b is the typical size of x86 cache lines
    /// 512b is the maximum possible size of x86 SIMD instruction
    ///
    /// 1024b is the typical size of ARM cache lines
    /// 2048b is the maximum possible size of ARM SIMD vectors
    ///
    constexpr std::size_t image_alignment = 256;

    ///
    /// \tparam T Channel type
    /// \tparam C Channel count
    /// \return Ideal alignment for pixel of the specified channel type and count
    template<class T, std::uint32_t C>
    constexpr std::size_t pixel_alignment = aul::is_pow2(C) ? alignof(T) * C : alignof(T);

    ///
    /// A class representing a tuple of primitive types to be used as the basis
    /// for the representation of an image.
    ///
    /// \tparam T Pixel channel type
    /// \tparam C Pixel channel count
    template<class T, std::uint32_t C>
    class alignas(pixel_alignment<T, C>) Pixel {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
    public:

        //=================================================
        // -ctors
        //=================================================

        template<class...Args, std::enable_if_t<(sizeof...(Args) == C) && (aul::are_same_types_v<Args...>)>>
        explicit Pixel(Args&&...args):
            components{args...} {}

        Pixel() = default;
        Pixel(const Pixel&) = default;
        Pixel(Pixel&&) noexcept = default;
        ~Pixel() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Pixel& operator=(const Pixel&) = default;
        Pixel& operator=(Pixel&&) noexcept = default;

        //=================================================
        // Subscript operators
        //=================================================

        T& operator[](int i) {
            return components[i];
        }

        T operator[](int i) const {
            return components[i];
        }

        //=================================================
        // Instance members
        //=================================================

    private:

        T components[C];

    };

    ///
    /// \tparam T Channel type
    /// \tparam C Channel count
    template<class T, std::uint32_t C>
    class Pixel_reference {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
    public:

        //=================================================
        // -ctors
        //=================================================

        ///
        /// \param p Pointer to pixel's first component. Must have alignment of
        ///     Pixel<T, C>
        explicit Pixel_reference(T* p):
            components(p) {}

        Pixel_reference(const Pixel_reference&) = default;
        ~Pixel_reference() = default;

        //=================================================
        // Assignment operators
        //=================================================

        template<class = typename std::enable_if_t<!std::is_const_v<T>>>
        Pixel_reference operator=(Pixel<T, C> pixel) {
            for (std::uint32_t i = 0; i < C; ++i) {
                components[i] = pixel[i];
            }
        }

        //=================================================
        // Subscript operators
        //=================================================

        T& operator[](int i) {
            return components[i];
        }

        T operator[](int i) const {
            return components[i];
        }

        //=================================================
        // Danger!
        //=================================================

        ///
        /// Allows for &image[x][y] syntax
        ///
        /// \return Pointer to pixel's components
        T* operator&() const {
            return components;
        }

        operator Pixel<T, C>() const {
            Pixel<T, C> ret{};
            for (std::uint32_t i = 0; i < C; ++i) {
                ret[i] = components[i];
            }
            return ret;
        }

        //=================================================
        // Instance members
        //=================================================

    private:

        T* components = nullptr;

    };

    class Image_base {
    public:

        //=================================================
        // Type aliases
        //=================================================

        using size_type = std::uint32_t;
        using difference_type = std::int32_t;

        //=================================================
        // -ctors
        //=================================================

        Image_base(size_type w, size_type h):
            w(w),
            h(h) {}

        Image_base() = default;
        Image_base(const Image_base&) = default;
        Image_base(Image_base&&) = default;
        ~Image_base() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Image_base& operator=(const Image_base&) = default;
        Image_base& operator=(Image_base&&) = default;

        //=================================================
        // Accessors
        //=================================================

        ///
        /// \return Image width in pixels
        [[nodiscard]]
        std::uint32_t width() const;

        ///
        /// \return Image height in pixels
        [[nodiscard]]
        std::uint32_t height() const;

        ///
        /// \return Tuple containing image width and height
        [[nodiscard]]
        std::array<std::uint32_t, 2> dimensions() const;

        ///
        /// \return Number of pixels in image
        [[nodiscard]]
        std::uint32_t size() const;

        ///
        /// \return Maximum number of pixels image may hold
        [[nodiscard]]
        std::uint32_t max_size() const;

        ///
        /// \return True if image contians zero pixels
        [[nodiscard]]
        bool empty() const;

        //=================================================
        // Instance members
        //=================================================

    protected:

        std::uint32_t w = 0;

        std::uint32_t h = 0;

    };

}

#endif //AGS_IMG_IMAGE_HPP
