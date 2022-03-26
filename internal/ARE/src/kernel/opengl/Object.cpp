//
// Created by avereniect on 1/9/22.
//
#include "Object.hpp"

#include <utility>

namespace ags::are::gl43 {

    Object::Object(Object&& other) noexcept:
        id(std::exchange(other.id, 0)) {}

    Object& Object::operator=(Object&& rhs) noexcept {
        id = std::exchange(rhs.id, 0);
        return *this;
    }

    GLuint Object::get_id() const {
        return id;
    }

}