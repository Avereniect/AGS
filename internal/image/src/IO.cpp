//
// Created by avereniect on 5/28/22.
//
#include <ags/image/IO.hpp>

#include <ags/Types.hpp>
#include <ags/Logging.hpp>

#include <libpng/png.h>

namespace ags::image {

    std::unique_ptr<Image> read_png(std::string_view view) {
        FILE* fp = fopen(view.data(), "rb");

        if (!fp) {
            AGS_ERROR(
                "{0}:\n{1}{2}",
                "Error encountered at " AGS_CODE_LOCATION,
                "Could not open file at path: ",
                view.data()
            );
            return {nullptr};
        }

        constexpr std::size_t header_size = 8;
        std::uint8_t header[header_size];
        std::size_t bytes_read = fread(header, 1, header_size, fp);

        if (bytes_read != header_size) {
            //TODO: Report error
            return {};
        }

        bool is_not_png = png_sig_cmp(header, 0, header_size);
        if (is_not_png) {
            AGS_ERROR(
                "{0}:\n{1}{2}",
                "Error encountered at " AGS_CODE_LOCATION,
                "File at specified path was not a PNG: ",
                view.data()
            );
            return {nullptr};
        }

        png_struct* png = png_create_read_struct(
            PNG_LIBPNG_VER_STRING,
            nullptr, //Use default error handling
            nullptr, //Use default error handling
            nullptr  //Use default error handling
        );

        if (!png) {
            AGS_ERROR(
                "{0}:\n{1}",
                "Error encountered at " AGS_CODE_LOCATION,
                "Error with Libpng: Failed to create_png_struct"
            );
            return {nullptr};
        }

        png_info* info = png_create_info_struct(png);
        if (!info) {
            png_destroy_read_struct(&png, nullptr, nullptr);
            //TODO: Log error
            return {nullptr};
        }

        png_infop end_info = png_create_info_struct(png);
        if (!end_info) {
            png_destroy_read_struct(&png, nullptr, nullptr);
            return {nullptr};
        }

        std::uint32_t w, h;
        int bit_depth, color_type, interlace_method, compression_method, filter_method;

        png_get_IHDR(
            png, info,
            &w, &h,
            &bit_depth,
            &color_type,
            &interlace_method,
            &compression_method,
            &filter_method
        );

        if (color_type == PNG_COLOR_TYPE_PALETTE) {
            png_set_palette_to_rgb(png);
        }

        if (bit_depth < 8) {
            png_set_packing(png);
        }

        std::vector<png_byte*> rows;
        rows.resize(h);

        int channel_count =
            (color_type == PNG_COLOR_TYPE_GRAY) ? 1 :
            (color_type == PNG_COLOR_TYPE_GA)   ? 2 :
            (color_type == PNG_COLOR_TYPE_RGB)  ? 3 :
            (color_type == PNG_COLOR_TYPE_RGBA) ? 4 :
        0;

        int pixel_size = (bit_depth <= 8) ? 1: 2;

        std::unique_ptr<Image> ret{nullptr};

        std::vector<char*> row_pointers{};
        rows.resize(h);

        /*
        //TODO: Complete
        if (pixel_size == 1) {
            switch (channel_count) {
            case 1:
                ret = std::unique_ptr<Pixel_buffer<std::uint8_t, 1>>{w, h};

                break;
            case 2:
                ret = std::unique_ptr<Pixel_buffer<std::uint8_t, 2>>{w, h};
                break;
            case 3:
                ret = std::unique_ptr<Pixel_buffer<std::uint8_t, 3>>{w, h};
                break;
            case 4:
                ret = std::unique_ptr<Pixel_buffer<std::uint8_t, 4>>{w, h};
                break;
            }
        } else {
            switch (channel_count) {
            case 1:
                ret = std::unique_ptr<Pixel_buffer<std::uint16_t, 1>>{};
                break;
            case 2:
                ret = std::unique_ptr<Pixel_buffer<std::uint16_t, 2>>{};
                break;
            case 3:
                ret = std::unique_ptr<Pixel_buffer<std::uint16_t, 3>>{};
                break;
            case 4:
                ret = std::unique_ptr<Pixel_buffer<std::uint16_t, 4>>{};
                break;
            }
        }
        */

        /*
        char* output = ret.get()->data();

        for (int i = 0; i < rows.size(); ++i) {
            rows[i] = output + i * (pixel_size * channel_count * w);
        }

        png_read_image(png, rows.data());
        */

        return ret;
    }

    void write_png(std::uint32_t w, std::uint32_t h, std::uint32_t c, Primitive type, const void* data, std::string_view path) {
        FILE* fp = fopen(path.data(), "w");
        if (fp == nullptr) {
            AGS_ERROR("Error encountered in {}:\n Failed to open file {} for writing", AGS_CODE_LOCATION, path.data());
            return;
        }

        png_struct* png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (png == nullptr) {
            AGS_ERROR("Error encountered in {}:\n Failed to create libPNG png struct", AGS_CODE_LOCATION);
            return;
        }

        png_infop info = png_create_info_struct(png);
        if (info == nullptr) {
            AGS_ERROR("Error encountered in {}:\n Failed to create libPNG info struct", AGS_CODE_LOCATION);
            return;
        }

        int color = 0;
        switch (c) {
        case 1: color = PNG_COLOR_TYPE_GRAY; break;
        case 2: color = PNG_COLOR_TYPE_GA;   break;
        case 3: color = PNG_COLOR_TYPE_RGB;  break;
        case 4: color = PNG_COLOR_TYPE_RGBA; break;
        default:
            ; //This should just never happen
        }

        png_init_io(png, fp);
        png_set_IHDR(
            png,
            info,
            w, h,
            int(size_of_primitive(type) * 8),
            color,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_BASE,
            PNG_FILTER_TYPE_BASE
        );

        png_write_info(png, info);

        std::size_t row_width = w * size_of_primitive(type) * c;
        for (std::uint32_t i = 0; i < h; ++i) {
            const unsigned char* row = reinterpret_cast<const unsigned char*>(data) + row_width * i;
            png_write_row(png, row);
        }
        png_write_end(png, nullptr);

        fclose(fp);
        png_free_data(png, info, PNG_FREE_ALL, -1);
        png_destroy_write_struct(&png, (png_infopp)NULL);
    }


    void write_png(const Pixel_buffer<std::uint8_t, 1>& buf, std::string_view path) {
        return write_png(buf.width(), buf.height(), 1, Primitive::UINT8, buf.data(), path);
    }

    void write_png(const Pixel_buffer<std::uint8_t, 2>& buf, std::string_view path) {
        return write_png(buf.width(), buf.height(), 2, Primitive::UINT8, buf.data(), path);
    }

    void write_png(const Pixel_buffer<std::uint8_t, 3>& buf, std::string_view path) {
        return write_png(buf.width(), buf.height(), 3, Primitive::UINT8, buf.data(), path);
    }

    void write_png(const Pixel_buffer<std::uint8_t, 4>& buf, std::string_view path) {
        return write_png(buf.width(), buf.height(), 4, Primitive::UINT8, buf.data(), path);
    }


    void write_png(const Pixel_buffer<std::uint16_t, 1>& buf, std::string_view path) {
        return write_png(buf.width(), buf.height(), 1, Primitive::UINT16, buf.data(), path);
    }

    void write_png(const Pixel_buffer<std::uint16_t, 2>& buf, std::string_view path) {
        return write_png(buf.width(), buf.height(), 2, Primitive::UINT16, buf.data(), path);
    }

    void write_png(const Pixel_buffer<std::uint16_t, 3>& buf, std::string_view path) {
        return write_png(buf.width(), buf.height(), 3, Primitive::UINT16, buf.data(), path);
    }

    void write_png(const Pixel_buffer<std::uint16_t, 4>& buf, std::string_view path) {
        return write_png(buf.width(), buf.height(), 4, Primitive::UINT16, buf.data(), path);
    }

}
