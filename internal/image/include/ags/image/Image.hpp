//
// Created by avereniect on 11/27/21.
//

#ifndef AGS_IMAGE_IMAGE_HPP
#define AGS_IMAGE_IMAGE_HPP

#include <aul/Bits.hpp>
#include <aul/Utility.hpp>

#include <algorithm>
#include <array>
#include <cstdint>

namespace ags::image {

    //=====================================================
    // Enums
    //=====================================================

    enum class Channel_format : std::uint8_t {
        NULL_CHANNEL_FORMAT,
        X,
        XY,
        XYZ,
        XYZW
    };

    //=====================================================
    // Constants
    //=====================================================

    ///
    /// Constant used to indicate that an image data structure should have a
    /// dynamic number of channels.
    ///
    constexpr std::size_t dynamic_channel_count = 0;

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
    /// Constant which evaluates to true if T, is suitable for use as a channel
    /// type for the image classes offered by the image module.
    ///
    /// \tparam T Arbitrary type
    template<class T>
    constexpr bool is_channel_type_v = std::is_integral_v<T> || std::is_floating_point_v<T>;

    //=====================================================
    // Pixel classes
    //=====================================================

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

        template<
            class...Args,
            class = typename std::enable_if_t<
                (sizeof...(Args) == C) /*&&
                (aul::are_same_types_v<T, typename std::decay<Args>::type...>) */
            >
        >
        explicit Pixel(Args&&...args):
            components{static_cast<T>(args)...} {}

        template<std::uint32_t C2, class = typename std::enable_if_t<C2 < C>>
        explicit Pixel(Pixel<T, C2> pix) {
            std::copy_n(pix.components, C2, components);
        }

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

        T& operator[](std::uint32_t i) {
            return components[i];
        }

        T operator[](std::uint32_t i) const {
            return components[i];
        }

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        T* data() noexcept {
            return components;
        }

        [[nodiscard]]
        const T* data() const noexcept {
            return components;
        }

        //=================================================
        // Instance members
        //=================================================

    private:

        T components[C];

    };

    ///
    /// This class is used to avoid having to type pun. Image classes represent
    /// images as simple arrays of the channel type but in practice this data is
    /// accessed in terms of pixels. However this introduces the need for type
    /// punning as an array of T cannot alias an array of type Pixel<T, C>.
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

            return *this;
        }

        //=================================================
        // Subscript operators
        //=================================================

        T& operator[](std::uint32_t i) {
            return components[i];
        }

        T operator[](std::uint32_t i) const {
            return components[i];
        }

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        T* data() noexcept {
            return components;
        }

        [[nodiscard]]
        const T* data() const noexcept {
            return components;
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

    ///
    /// Base class for all image classes in AGS_IMAGE module.
    ///
    class Image {
    public:

        //=================================================
        // Type aliases
        //=================================================

        using size_type = std::uint32_t;
        using difference_type = std::int32_t;

        //=================================================
        // -ctors
        //=================================================

        Image(size_type w, size_type h):
            w(w),
            h(h) {}

        Image() = default;
        Image(const Image&) = default;
        Image(Image&&) = default;
        virtual ~Image() = 0;

        //=================================================
        // Assignment operators
        //=================================================

        Image& operator=(const Image&) = default;
        Image& operator=(Image&&) = default;

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

        ///
        /// \return Number of color channels in image
        [[nodiscard]]
        virtual std::uint32_t depth() const noexcept = 0;

        //=================================================
        // Instance members
        //=================================================

    protected:

        std::uint32_t w = 0;
        std::uint32_t h = 0;

    };

}

#endif //AGS_IMAGE_IMAGE_HPP
