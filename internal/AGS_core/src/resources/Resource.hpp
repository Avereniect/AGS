//
// Created by avereniect on 9/6/22.
//

#ifndef AGS_RESOURCE_RESOURCE_HPP
#define AGS_RESOURCE_RESOURCE_HPP

#include <string>
#include <string_view>

namespace ags::resource {

    class Resource {
    public:

        //=================================================
        // -ctors
        //=================================================

        explicit Resource(const std::string& path):
            resource_path(path) {}

        explicit Resource(std::string&& path):
            resource_path(std::move(path)) {}

        explicit Resource(std::string_view path):
            resource_path(path) {}

        //=================================================
        // Assignment operators
        //=================================================

        //=================================================
        // Accessors
        //=================================================

        //=================================================
        // Mutators
        //=================================================

    protected:

        //=================================================
        // Instance members
        //=================================================

        std::string resource_path;

        bool loaded = false;

    };

}

#endif //AGS_RESOURCE_RESOURCE_HPP
