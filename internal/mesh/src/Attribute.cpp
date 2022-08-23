//
// Created by avereniect on 8/19/22.
//
#include "ags/mesh/Attribute.hpp"

namespace ags::mesh {

    Attribute_handle::Attribute_handle(Primitive p, Attribute_width w, void* ptr):
        primitive(p),
        components(w),
        ptr(ptr) {}

    Primitive Attribute_handle::type() const {
        return primitive;
    }

    Attribute_width Attribute_handle::width() const {
        return components;
    }

    void* Attribute_handle::handle() {
        return ptr;
    }

    const void* Attribute_handle::handle() const {
        return ptr;
    }

    void Attribute_handle::set_handle(void* p) {
        ptr = p;
    }

}
