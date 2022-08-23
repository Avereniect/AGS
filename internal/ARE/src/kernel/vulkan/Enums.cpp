//
// Created by avereniect on 3/12/22.
//
#include "Enum.hpp"

namespace ags::are::vk_kernel {

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

    vk::Format to_native_enum(Channel_format f, Primitive primitive) {
        switch (primitive) {
            case Primitive::UINT8: {
                switch (f) {
                case Channel_format::X: return vk::Format::e;
                }
            }
            case Primitive::UINT16: {

            }
            case Primitive::FLOAT32: {

            }
        }

        switch (f) {
        case Channel_format::X: return vk::Format::e;
        default: return vk::Format::eUndefined;
        }
    }

    vk::Format to_native_enum(Stencil_format f) {
        switch (f) {
        case Stencil_format::NULL_STENCIL_FORMAT: return vk::Format::eUndefined;
        case Stencil_format::STENCIL8: return vk::Format::eS8Uint;
        default:
            ; //Error
        }
    }

    vk::Format to_native_enum(Depth_format f) {
        switch (f) {
        case Depth_format::NULL_DEPTH_FORMAT: return vk::Format::eUndefined;
        case Depth_format::INT24: return vk::Format::eX8D24UnormPack32;
        default:
            ; //Error
        }
    }

    vk::Format to_native_enum(Depth_stencil_format f) {
        switch (f) {
        case Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT: return vk::Format::eUndefined;
        case Depth_stencil_format::INT24: return vk::Format::eX8D24UnormPack32;
        case Depth_stencil_format::FLOAT32: return vk::Format::eD32Sfloat;
        case Depth_stencil_format::STENCIL8: return vk::Format::eS8Uint;
        case Depth_stencil_format::INT24_STENCIL8: return vk::Format::eD24UnormS8Uint;
        case Depth_stencil_format::FLOAT32_STENCIL8: return vk::Format::eD32SfloatS8Uint;
        default:
            ; //Error;
        }
    }

}
