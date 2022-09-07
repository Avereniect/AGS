//
// Created by avereniect on 6/26/22.
//

#ifndef AGS_TEXTURE_KERNEL_HPP
#define AGS_TEXTURE_KERNEL_HPP

#include <ags/Graphics_includes.hpp>

#include "Device_kernel.hpp"
#include "Enums.hpp"

#include <tuple>

#include <aul/containers/Matrix.hpp>

namespace ags::are::vk_kernel {

    class Texture_kernel : public Device_kernel {
    public:

        ///
        /// Checks to see if a texture with the specified channel format and
        /// channel type is supported. If the image type is not supported then
        ///
        /// \param f Image channel format enum
        /// \param p Image channel primitive enum
        /// \return True if a texture with the specified channel
        ///     format-primitive combination is supported. False otherwise
        static bool query_texture_support(Channel_format f, Primitive p);

        static std::pair<Channel_format, Primitive> suitable_texture_format(Channel_format f, Primitive p);

    private:

        static aul::Matrix<bool, 2> supported_texture_formats;

    };

}

#endif //AGS_TEXTURE_KERNEL_HPP
