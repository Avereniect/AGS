//
// Created by avereniect on 3/12/22.
//
#include "Enum.hpp"

namespace ags::are::vk10 {

    vk::SampleCountFlagBits to_native_enum(Sample_count s) {
        switch (s) {
        case Sample_count::S1: return vk::SampleCountFlagBits::e1;
        case Sample_count::S2: return vk::SampleCountFlagBits::e2;
        case Sample_count::S4: return vk::SampleCountFlagBits::e4;
        case Sample_count::S8: return vk::SampleCountFlagBits::e8;
        case Sample_count::S16: return vk::SampleCountFlagBits::e16;
        case Sample_count::S32: return vk::SampleCountFlagBits::e32;
        default:
            ; //Error
        }
    }

}
