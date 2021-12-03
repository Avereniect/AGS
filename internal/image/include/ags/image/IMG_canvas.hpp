//
// Created by avereniect on 11/29/21.
//

#ifndef AGS_IMG_CANVAS_HPP
#define AGS_IMG_CANVAS_HPP

#include "IMG_image.hpp"

#include "aul/containers/Matrix.hpp"

namespace ags::image {

    template<class T, std::uint32_t C>
    class Canvas_subscriptor {
    public:

        using pointer = T*;

        using size_type = std::uint32_t;

        Canvas_subscriptor() = delete;
        Canvas_subscriptor(const Canvas_subscriptor&) = delete;
        Canvas_subscriptor(Canvas_subscriptor&&) = delete;
        ~Canvas_subscriptor() = default;

        Canvas_subscriptor& operator=(const Canvas_subscriptor) = delete;
        Canvas_subscriptor& operator=(Canvas_subscriptor&&) = delete;

        T& operator[](size_type y) {
            std::uint32_t tile_y = y / tile_size;
            std::uint32_t y_offset = y % tile_size;

            auto* tile = tile_matrix[tile_x + tile_y * x_tiles];

            return tile[x_offset + y_offset * tile_size];
        }

        T& operator[](size_type y) const {
            std::uint32_t tile_y = y / tile_size;
            std::uint32_t y_offset = y % tile_size;

            auto* tile = tile_matrix[tile_x + tile_y * x_tiles];

            return tile[x_offset + y_offset * tile_size];
        }

    private:

        pointer tile_matrix;

        std::uint32_t x_tiles;

        std::uint32_t tile_x;
        std::uint32_t x_offset;
        std::uint32_t tile_size;
    };

    template<class T, std::uint32_t C>
    class Canvas : Image_base {
        using base = Image_base;
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

        ///
        /// \param w
        /// \param h
        /// \param color
        /// \param tile_size Size of image tiles TODO: Create reasonable default
        Canvas(std::uint32_t w, std::uint32_t h, pixel_type color, std::uint32_t tile_size = 16);

        Canvas(std::uint32_t w, std::uint32_t h, std::uint32_t tile_size):
            Canvas(w, h, {}, tile_size) {}

        Canvas(std::uint32_t w, std::uint32_t h, pixel_type color = {}):
            Canvas(w, h, color) {}


        Canvas(const Canvas& canvas);

        Canvas(Canvas&& canvas);

        ~Canvas() {
            clear();
        }

        //=================================================
        // Assignment operators
        //=================================================

        Canvas& operator=(const Canvas&) = default;
        Canvas& operator=(Canvas&&) = default;

        //=================================================
        // Subscript operators
        //=================================================

        Canvas_subscriptor<T, C> operator[](size_type x);

        Canvas_subscriptor<T, C> operator[](size_type x) const;

        //=================================================
        // Mutators
        //=================================================

        /*
        void resize(size_type w, size_type h, pixel_type color = {}) {
            if (!w || !h) {
                clear();
                return;
            }

            //TODO: Complete implementation
        }
        */

        void clear() {
            for (auto t : tiles) {
                delete[] t;
            }

            tiles.clear();

            base::w = 0;
            base::h = 0;
        }

        //=================================================
        // Instance members
        //=================================================

    private:

        ///
        /// Matrix containing pointers to tiles. Each tile is of the size
        ///
        aul::Matrix<pointer, 2> tiles;

        ///
        /// Side lengths of tiles. Cannot be changed after construction of
        /// object except after moves.
        ///
        std::uint32_t tile_size = 0;
    };

}

#endif //AGS_IMG_CANVAS_HPP
