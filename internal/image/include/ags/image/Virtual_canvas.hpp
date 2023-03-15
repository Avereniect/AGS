#ifndef AGS_VIRTUAL_CANVAS_HPP
#define AGS_VIRTUAL_CANVAS_HPP

#include <cstdint>
#include <vector>
#include <type_traits>

namespace ags::image {

    template<class T, std::uint32_t C>
    class Virtual_canvas_tile {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
    public:

        //=================================================
        // Static constants
        //=================================================

        static constexpr std::uint32_t tile_width = 16;

        //=================================================
        // Type aliases
        //=================================================

        using pointer = T*;

        using size_type = std::size_t;

        //=================================================
        // -ctors
        //=================================================



        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        size_type size() const {
            return tile_width * tile_width;
        }

        [[nodiscard]]
        pointer data() const {
            return ptr;
        }

    private:

        //=================================================
        // Instance members
        //=================================================



        //=================================================
        // Helper functions
        //=================================================



    };

    template<class T, std::uint32_t C>
    class Virtual_canvas_tile_matrix {
    public:

    private:

    };

    template<class T, std::uint32_t C>
    class Virtual_canvas_tile_cache {
    public:

    private:

    };

    ///
    /// A virtual canvas is a data structure meant to abstract away from
    ///
    /// \tparam T Channel type
    /// \tparam C Channel count
    template<class T, std::uint32_t C>
    class Virtual_canvas {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
    public:

        //=================================================
        // Static constants
        //=================================================

        static constexpr std::uint32_t tile_width = Virtual_canvas_tile<T, C>::tile_width;

        //=================================================
        // -ctors
        //=================================================

        Virtual_canvas() = default;

        ~Virtual_canvas() {
            clear();
        }

        //=================================================
        // Assignment operators
        //=================================================

        Virtual_canvas& operator=(const Virtual_canvas&);
        Virtual_canvas& operator=(Virtual_canvas&&);

        //=================================================
        // Element mutators
        //=================================================

        ///
        /// Empties the current canvas's contents.
        ///
        void clear() {
            //TODO: Implement
        }

        //=================================================
        // Accessors
        //=================================================

        //TODO: Create accessors

    private:

        //=================================================
        // Instance members
        //=================================================

        ///
        /// Contains the matrices which represent the various levels of the
        /// image
        ///
        std::vector<Virtual_canvas_tile_matrix<T, C>> levels;

        //=================================================
        // Helper functions
        //=================================================



    };

}

#endif //AGS_VIRTUAL_CANVAS_HPP
