//
// Created by avereniect on 12/8/21.
//

#ifndef AGS_IMG_VIRTUAL_CANVAS_HPP
#define AGS_IMG_VIRTUAL_CANVAS_HPP

#include <cstdint>
#include <type_traits>

namespace ags::image {

    ///
    /// \tparam T Channel type
    /// \tparam C Channel count
    template<class T, std::uint32_t C>
    class Virtual_canvas {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
    public:

        //=================================================
        // -ctors
        //=================================================

        //=================================================
        // Assignment operators
        //=================================================


    private:
    };

}

#endif //AGS_IMG_VIRTUAL_CANVAS_HPP
