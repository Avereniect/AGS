//
// Created by avereniect on 9/6/22.
//

#ifndef AGS_RESOURCE_IMAGE_HPP
#define AGS_RESOURCE_IMAGE_HPP

#include "Resource.hpp"

namespace ags::resource {

    class Image_resource : public Resource {
    public:

        //=================================================
        // -ctors
        //=================================================

        using Resource::Resource;

        //=================================================
        // Assignment operators
        //=================================================

        Image_resource& operator=(const Image_resource&);
        Image_resource& operator=(Image_resource&&) noexcept;

        //=================================================
        // Accessors
        //=================================================



        //=================================================
        // Mutators
        //=================================================

    private:

        //=================================================
        // Instance members
        //=================================================



    };

}

#endif //AGS_RESOURCE_IMAGE_HPP
