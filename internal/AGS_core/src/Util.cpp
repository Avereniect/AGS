//
// Created by avereniect on 8/9/22.
//
#include <ags/Util.hpp>

namespace ags {

    std::string read_ascii_text(std::string_view path) {
        std::string ret{};

        FILE *f = fopen(path.data(), "r");
        fseek(f, 0, SEEK_END);
        std::size_t file_size = ftell(f);
        fseek(f, 0, SEEK_SET);

        ret.resize(file_size);
        auto read_byte_count = fread(ret.data(), 1, file_size, f);
        fclose(f);

        if (read_byte_count != file_size) {
            ret.resize(read_byte_count);
            //TODO: Log error
        }

        return  ret;
    }

}