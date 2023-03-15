#ifndef AGS_IMAGE_DYNAMIC_PIXEL_BUFFER_HPP
#define AGS_IMAGE_DYNAMIC_PIXEL_BUFFER_HPP

#include <ags/Types.hpp>
#include <aul/containers/Array_map.hpp>
#include <aul/Span.hpp>

#include <string_view>

namespace ags::image {

    class Dynamic_pixel_buffer {
    public:

        //=================================================
        // Helper Types
        //=================================================

        template<class P>
        struct Channel {
            Primitive type;
            P ptr;
        };

        //=================================================
        // Type aliases
        //=================================================

        using channel_attribute = Channel<void*>;
        using const_channel_attribtue = Channel<const void*>;

        //=================================================
        // -ctors
        //=================================================

        Dynamic_pixel_buffer() = default;
        Dynamic_pixel_buffer(const Dynamic_pixel_buffer&);
        Dynamic_pixel_buffer(Dynamic_pixel_buffer&&) noexcept;
        ~Dynamic_pixel_buffer();

        //=================================================
        // Assignment operators
        //=================================================

        //=================================================
        // Accessors
        //=================================================

        channel_attribute operator[](std::string_view view);

        const_channel_attribtue operator[](std::string_view view) const;

        //=================================================
        // Mutators
        //=================================================

        channel_attribute specify_channel(std::string_view name);

        void remove_channel(std::string_view name);

        void clear();

    private:

        //=================================================
        // Instance members
        //=================================================

        aul::Array_map<std::string, channel_attribute> channel_map;

    };

}

#endif //AGS_IMAGE_DYNAMIC_PIXEL_BUFFER_HPP
