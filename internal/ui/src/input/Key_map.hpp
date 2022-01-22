//
// Created by avereniect on 1/21/22.
//

#ifndef AGS_KEY_MAP_HPP
#define AGS_KEY_MAP_HPP

#include "Key_event.hpp"

#include <aul/containers/Array_map.hpp>

namespace ags::ui {

    using key_callback = int (*)();

    using Key_map = aul::Array_map<Key_event, key_callback>;

}

#endif //AGS_KEY_MAP_HPP
