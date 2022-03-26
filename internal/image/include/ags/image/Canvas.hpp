//
// Created by avereniect on 11/29/21.
//

#ifndef AGS_CANVAS_HPP
#define AGS_CANVAS_HPP

#include "Image.hpp"

#include "aul/containers/Matrix.hpp"

#include <aul/Math.hpp>

namespace ags::image {

    template<class T, std::uint32_t C>
    class Canvas_subscriptor {
    public:

        //=================================================
        // Type aliases
        //=================================================

        using pointer = T*;
        using size_type = std::uint32_t;

        //=================================================
        // -ctors
        //=================================================

        Canvas_subscriptor(
            pointer tile_matrix,
            size_type x_tiles,
            size_type tile_x,
            size_type x_offset,
            size_type tile_width
        ):
            tile_matrix(tile_matrix),
            x_tiles(x_tiles),
            tile_x(tile_x),
            x_offset(x_offset),
            tile_width(tile_width) {}

        Canvas_subscriptor() = delete;
        Canvas_subscriptor(const Canvas_subscriptor&) = delete;
        Canvas_subscriptor(Canvas_subscriptor&&) = delete;
        ~Canvas_subscriptor() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Canvas_subscriptor& operator=(const Canvas_subscriptor) = delete;
        Canvas_subscriptor& operator=(Canvas_subscriptor&&) = delete;

        //=================================================
        // Subscript operators
        //=================================================

        T& operator[](size_type y) {
            size_type tile_y = y / tile_width;
            size_type y_offset = y % tile_width;

            auto* tile = tile_matrix[tile_x + tile_y * x_tiles];

            return tile[x_offset + y_offset * tile_width];
        }

        const T& operator[](size_type y) const {
            size_type tile_y = y / tile_width;
            size_type y_offset = y % tile_width;

            auto* tile = tile_matrix[tile_x + tile_y * x_tiles];

            return tile[x_offset + y_offset * tile_width];
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        ///
        /// Pointer to 2D matrix of tile pointers
        ///
        pointer tile_matrix;

        ///
        /// Number of tiles in x direction
        ///
        size_type x_tiles;

        ///
        /// Subscript x tile index
        ///
        size_type tile_x;

        ///
        /// X offset within target tile
        ///
        size_type x_offset;

        ///
        /// Side lengths of tiles
        ///
        size_type tile_width;

    };

    ///
    /// A Canvas is an image class that is more suitable for image processing
    ///
    /// The image's contents are split up into square tiles which can be
    /// processed in a more cache friendly manner.
    ///
    /// \tparam T Channel type
    /// \tparam C Channel count
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
        /// \param w Image width
        /// \param h Image height
        /// \param color Default color to set pixels to
        /// \param tw Size of image tiles. Must be power of two
        Canvas(size_type w, size_type h, pixel_type color, size_type tw = 16):
            tiles({h, w}),
            tile_width(aul::ceil2(tw)) {

            auto tile_size = tile_width * tile_width;
            for (size_type y = 0; y < h; ++y) {
                for (size_type x = 0; x < w; ++x) {
                    for (size_type i = 0; i < tile_size; ++i) {
                        for (size_type j = 0; j < C; ++j) {
                            tiles[y][x][C * i + j] = color[j];
                        }
                    }
                }
            }
        }

        ///
        /// \param w Image width
        /// \param h Image height
        /// \param tw Width of tiles used internally. Must be power of two
        Canvas(size_type w, size_type h, size_type tw):
            Canvas(w, h, {}, aul::ceil2(tile_width)) {}

        ///
        /// \param w Image width
        /// \param h Image height
        /// \param color Default color to set pixels to
        Canvas(size_type w, size_type h, pixel_type color = {}):
            Canvas(w, h, color, 16) {}

        Canvas(const Canvas& src):
            tiles({src.tiles.dimensions()}),
            tile_width(src.tile_width) {

            auto tile_size = tile_width * tile_width;

            auto dims = src.dimensions();
            for (size_type y = 0; y < dims[1]; ++y) {
                for (size_type x = 0; x < dims[0]; ++x) {
                    tiles[y][x] = new channel_type[tile_size * C];

                    std::copy_n(src.tiles[y][x], tile_size * C, tiles[y][x]);
                }
            }
        }

        Canvas(Canvas&& src) noexcept:
            tiles(std::exchange(src.tiles, {})),
            tile_width(std::exchange(src.tile_width, 0)) {}

        ~Canvas() {
            clear();
        }

        //=================================================
        // Assignment operators
        //=================================================

        Canvas& operator=(const Canvas&) = default;
        Canvas& operator=(Canvas&&) noexcept = default;

        //=================================================
        // Subscript operators
        //=================================================

        Canvas_subscriptor<T, C> operator[](size_type x) {
            return Canvas_subscriptor<T, C>{
                tiles.data(),
                tiles.dimensions()[1],
                x / tile_width,
                x % tile_width,
                tile_width
            };
        }

        Canvas_subscriptor<const T, C> operator[](size_type x) const {
            return Canvas_subscriptor<const T, C>{
                tiles.data(),
                tiles.dimensions()[1],
                x / tile_width,
                x % tile_width,
                tile_width
            };
        }

        //=================================================
        // Mutators
        //=================================================

        ///
        /// Resizes the contents of the image
        ///
        /// If image dimensions are expanded, they are made
        ///
        /// If resizing can be done without editing tile contents then the
        /// program will take that approach
        ///
        /// \param w New image width
        /// \param h New image height
        /// \param x_offset X offset applied to contents of image after resize
        /// \param y_offset Y offset applied to contents of image after resize
        /// \param color Color to fill any new pixels with
        void resize(
            size_type w, size_type h,
            size_type x_offset, size_type y_offset,
            pixel_type color = {}
        ); /*{
            if ((w == 0) || (h == 0)) {
                clear();
                return;
            }

            size_type old_x_tiles = tiles.dimensions()[1];
            size_type old_y_tiles = tiles.dimensions()[0];

            size_type x_tiles = aul::divide_ceil(w, tile_width);
            size_type y_tiles = aul::divide_ceil(h, tile_width);

            tiles.resize(x_tiles, y_tiles);

            //TODO: Complete implementation
            //TODO: Consider if it's necessary to blank out tiles on shrinking
        }
        */

        ///
        /// Resets image's size to (0,0). Releases held allocation
        ///
        void clear() {
            for (auto t : tiles) {
                delete[] t;
            }

            tiles.clear();

            base::w = 0;
            base::h = 0;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        ///
        /// Matrix containing pointers to tiles. Each tile has dimensions
        /// tile_size
        ///
        aul::Matrix<pointer, 2> tiles;

        ///
        /// Side lengths of tiles. Cannot be changed after construction of
        /// object except after moves.
        ///
        std::uint32_t tile_width = 0;

    };

}

#endif //AGS_CANVAS_HPP
