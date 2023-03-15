#include "Enums.hpp"

namespace ags::are::vk_kernel {

    vk::SampleCountFlagBits to_native_enum(Sample_count s) {
        switch (s) {
        case Sample_count::S1: return vk::SampleCountFlagBits::e1;
        case Sample_count::S2: return vk::SampleCountFlagBits::e2;
        case Sample_count::S4: return vk::SampleCountFlagBits::e4;
        case Sample_count::S8: return vk::SampleCountFlagBits::e8;
        case Sample_count::S16: return vk::SampleCountFlagBits::e16;
        case Sample_count::S32: return vk::SampleCountFlagBits::e32;
        default: return vk::SampleCountFlagBits::e1; //Error //TODO: Log
        }
    }

    vk::Format to_native_enum(Channel_format f, Primitive primitive) {
        switch (primitive) {
            case Primitive::UINT8: {
                static constexpr vk::Format table[] {
                    vk::Format::eB8G8R8A8Unorm,
                    vk::Format::eB8G8R8A8Unorm, //TODO: Correct
                    vk::Format::eB8G8R8A8Unorm,
                    vk::Format::eB8G8R8A8Unorm
                };

                return table[static_cast<std::uint32_t>(f) - 1];
            }
            case Primitive::UINT16: {

            }
            case Primitive::FLOAT32: {

            }
        default:
            AGS_ERROR("Error encountered at {}\n{}", AGS_CODE_LOCATION, "Unrecognized enum value");
            return vk::Format::eUndefined;
        }
    }

    vk::Format to_native_enum(Stencil_format f) {
        switch (f) {
        case Stencil_format::NULL_STENCIL_FORMAT: return vk::Format::eUndefined;
        case Stencil_format::STENCIL8: return vk::Format::eS8Uint;
        default: return vk::Format::eUndefined; //Error TODO: log
        }
    }

    vk::Format to_native_enum(Depth_format f) {
        switch (f) {
        case Depth_format::NULL_DEPTH_FORMAT: return vk::Format::eUndefined;
        case Depth_format::INT24: return vk::Format::eX8D24UnormPack32;
        default:
            return vk::Format::eUndefined; //Error
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
            return vk::Format::eUndefined; //Error;
        }
    }

    vk::Format to_native_enum(Texture_format format) {
        //TODO: Complete implementation
        Primitive p = to_primitive(format);

        switch (p) {
            case Primitive::UINT8: {
                static constexpr vk::Format table[] {

                };

            }
            case Primitive::UINT16: {

            }
            case Primitive::UINT32: {

            }
            case Primitive::FLOAT16: {

            }
            case Primitive::FLOAT32: {

            }
            default: {
                return vk::Format::eUndefined;
            }
        }
    }

    vk::Format to_native_enum(Attribute_type type) {
        auto width = attribute_width(type);
        auto primitive = attribute_primitive(type);

        switch (primitive) {
        case Primitive::FLOAT32: {
            vk::Format table[] {
                vk::Format::eR32Sfloat,
                vk::Format::eR32G32Sfloat,
                vk::Format::eR32G32B32Sfloat,
                vk::Format::eR32G32B32A32Sfloat
            };

            return table[int(width) - 1];
        }

        case Primitive::UINT32: {
            vk::Format table[] {
                vk::Format::eR32Uint,
                vk::Format::eR32G32Uint,
                vk::Format::eR32G32B32Uint,
                vk::Format::eR32G32B32A32Uint
            };

            return table[int(width) - 1];
        }

        case Primitive::INT32: {
            vk::Format table[] {
                vk::Format::eR32Sint,
                vk::Format::eR32G32Sint,
                vk::Format::eR32G32B32Sint,
                vk::Format::eR32G32B32A32Sint
            };

            return table[int(width) - 1];
        }

        default:
            AGS_ERROR("Unrecognized are::Attribute_type enum");
            return vk::Format::eUndefined;
        }
    }

}
