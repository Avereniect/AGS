//
// Created by avereniect on 11/27/21.
//

#ifndef AGS_PIXEL_BUFFER_HPP
#define AGS_PIXEL_BUFFER_HPP

#include "Image.hpp"

#include <algorithm>
#include <utility>

namespace ags::image {

    ///
    /// Convenience class which allows subscripting on Pixel_buffer and
    /// Pixel_buffer_view objects to have a more convenient ordering of [x][y]
    /// instead of [y][x].
    ///
    /// \tparam T Pixel_buffer channel type
    /// \tparam C Pixel_buffer channel count
    template<class T, std::uint32_t C>
    class Pixel_buffer_subscripter {
    public:

        //=================================================
        // -ctors
        //=================================================

        Pixel_buffer_subscripter(T* ptr, std::uint32_t w, std::uint32_t x):
            ptr(ptr),
            w(w),
            x(x) {}

        Pixel_buffer_subscripter() = delete;
        Pixel_buffer_subscripter(const Pixel_buffer_subscripter&) = delete;
        Pixel_buffer_subscripter(Pixel_buffer_subscripter&&) = delete;
        ~Pixel_buffer_subscripter() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Pixel_buffer_subscripter& operator=(const Pixel_buffer_subscripter&) = delete;
        Pixel_buffer_subscripter& operator=(Pixel_buffer_subscripter&&) = delete;

        //=================================================
        // Subscript operators
        //=================================================

        Pixel_reference<T, C> operator[](std::uint32_t y) {
            return Pixel_reference<T, C>{ptr + C * (y * w + x)};
        }

        //=================================================
        // Instance members
        //=================================================

    private:

        T* ptr;
        std::uint32_t w;
        std::uint32_t x;

    };

    template<class T, std::uint32_t C>
    class Pixel_buffer_base : public Image_base {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
    public:


        //=================================================
        // Type aliases
        //=================================================

        using value_type = T;

        using channel_type = T;
        using pixel_type = Pixel<channel_type , C>;

        using pointer = T*;
        using const_pointer = const T*;

        using size_type = Image_base::size_type;
        using difference_type = Image_base::difference_type;

        using reference = Pixel_reference<T, C>;
        using const_reference = Pixel_reference<const T, C>;

        //=================================================
        // -ctors
        //=================================================

        Pixel_buffer_base(size_type w, size_type h, pointer data):
            Image_base(w, h),
            data(data) {}

        Pixel_buffer_base() = default;
        Pixel_buffer_base(const Pixel_buffer_base&) = delete;

        Pixel_buffer_base(Pixel_buffer_base&& base) noexcept:
            data(std::exchange(base.ptr, nullptr)) {}

        ~Pixel_buffer_base() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Pixel_buffer_base& operator=(const Pixel_buffer_base&) = delete;

        Pixel_buffer_base& operator=(Pixel_buffer_base&& base) noexcept {
            data = std::exchange(base.ptr, nullptr);
            return *this;
        }

        //=================================================
        // Subscript operators
        //=================================================

        reference operator[](std::uint32_t x) {
            return reference{data, w, x};
        }

        const_reference operator[](std::uint32_t x) const {
            return const_reference{data, w, x};
        }

        //=================================================
        // Instance members
        //=================================================

    protected:

        pointer data;

    };

    ///
    /// A Pixel_buffer internally represents an image in a way that facilitates
    /// interoperability with other libraries and API's.
    ///
    /// The image is stored as
    /// a single contiguous array where the channels of each pixels are
    /// interleaved, e.g. rgbargbargba
    ///
    /// \tparam T Channel type
    /// \tparam C Channel count
    template<class T, std::uint32_t C>
    class Pixel_buffer : public Pixel_buffer_base<T, C>{
        using base = Pixel_buffer_base<T, C>;
    public:

        using channel_type = typename base::channel_type;
        using pixel_type = typename base::pixel_type;

        using pointer = typename base::pointer;
        using const_pointer = typename base::const_pointer;

        using size_type = typename base::size_type;
        using difference_type = typename base::difference_type;

        //=================================================
        // -ctors
        //=================================================

        Pixel_buffer(size_type w, size_type h, pointer data):
            base(w, h, new(std::align_val_t(image_alignment)) channel_type[w * h * C]) {

            std::copy_n(data, w * h * C, base::data);
        }

        Pixel_buffer(size_type w, size_type h, pixel_type color = {}):
            base(w, h, new(std::align_val_t(image_alignment)) channel_type[w * h * C]) {

            for (std::uint32_t i = 0; i < (w * h); ++i) {
                for (std::uint32_t j = 0; j < C; ++j) {
                    base::data[i * C + j] = color[j];
                }
            }
        }

        Pixel_buffer():
            base(0, 0, nullptr) {}

        Pixel_buffer(const Pixel_buffer& pb):
            base(pb.w, pb.h, new (std::align_val_t(image_alignment)) channel_type[pb.w * pb.h * C]) {

            std::copy_n(pb.data, pb.size() * C, base::data);
        }

        Pixel_buffer(Pixel_buffer&& pb) noexcept:
            base(pb.w, pb.h, pb.data) {

            pb.w = 0;
            pb.h = 0;
            pb.data = nullptr;
        }

        ~Pixel_buffer() {
            clear();
        }

        //=================================================
        // Assignment operators
        //=================================================

        Pixel_buffer& operator=(const Pixel_buffer& rhs) {
            if (this == &rhs) {
                return *this;
            }

            delete[] base::data;
            base::data = std::exchange(rhs.data, nullptr);
            base::w = std::exchange(rhs.w, 0);
            base::w = std::exchange(rhs.h, 0);

            return *this;
        }

        Pixel_buffer& operator=(Pixel_buffer&& rhs) noexcept {
            base::data = std::exchange(rhs.data, nullptr);
            base::w = std::exchange(rhs.w, 0);
            base::h = std::exchange(rhs.h, 0);

            return *this;
        }

        //=================================================
        // Mutators
        //=================================================

        void clear() {
            delete[] base::data;
        }

    };

    ///
    /// A non-owning class that presents the same interface as a Pixel_buffer
    /// but over an array that was not
    ///
    /// The specified array should have size() * C elements and the dimensions
    /// of the image it represents should match those passed to the constructor
    /// of this class.
    ///
    /// \tparam T Channel type
    /// \tparam C Channel count
    template<class T, std::uint32_t C>
    class Pixel_buffer_view : public Pixel_buffer_base<T, C> {
        using base = Pixel_buffer_base<T, C>;
    public:

        //=================================================
        // Type aliases
        //=================================================

        using channel_type = typename base::channel_type;
        using pixel_type = typename base::pixel_type;

        using pointer = typename base::pointer;
        using const_pointer = typename base::const_pointer;

        using size_type = typename base::size_type;
        using difference_type = typename base::difference_type;

        //=================================================
        // -ctors
        //=================================================

        Pixel_buffer_view(size_type w, size_type h, pointer data):
            base(w, h, data) {}

        Pixel_buffer_view() = default;
        Pixel_buffer_view(const Pixel_buffer_view&) = default;
        Pixel_buffer_view(Pixel_buffer_view&&) noexcept = default;
        ~Pixel_buffer_view() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Pixel_buffer_view& operator=(const Pixel_buffer_view&) = default;
        Pixel_buffer_view& operator=(Pixel_buffer_view&&) noexcept = default;

    };

    //=====================================================
    // Explicit template instantiations
    //=====================================================

    template class Pixel_buffer<std::uint8_t, 1>;
    template class Pixel_buffer<std::uint8_t, 2>;
    template class Pixel_buffer<std::uint8_t, 3>;
    template class Pixel_buffer<std::uint8_t, 4>;

    template class Pixel_buffer<std::uint16_t, 1>;
    template class Pixel_buffer<std::uint16_t, 2>;
    template class Pixel_buffer<std::uint16_t, 3>;
    template class Pixel_buffer<std::uint16_t, 4>;

    template class Pixel_buffer<float, 1>;
    template class Pixel_buffer<float, 2>;
    template class Pixel_buffer<float, 3>;
    template class Pixel_buffer<float, 4>;


    template class Pixel_buffer_view<std::uint8_t, 1>;
    template class Pixel_buffer_view<std::uint8_t, 2>;
    template class Pixel_buffer_view<std::uint8_t, 3>;
    template class Pixel_buffer_view<std::uint8_t, 4>;

    template class Pixel_buffer_view<std::uint16_t, 1>;
    template class Pixel_buffer_view<std::uint16_t, 2>;
    template class Pixel_buffer_view<std::uint16_t, 3>;
    template class Pixel_buffer_view<std::uint16_t, 4>;

    template class Pixel_buffer_view<float, 1>;
    template class Pixel_buffer_view<float, 2>;
    template class Pixel_buffer_view<float, 3>;
    template class Pixel_buffer_view<float, 4>;

}

#endif //AGS_PIXEL_BUFFER_HPP
