//
// Created by avereniect on 12/6/21.
//

#include "VOX_chunked_volume.hpp"

#include <aul/containers/Array_map.hpp>

namespace ags::voxel {

    Raw_chunk decompress(const Chunk& chunk) {

    }

    std::tuple<Chunk, Chunk_palette> compress(const Raw_chunk& raw_chunk) {
        Chunk chunk{};
        Chunk_palette palette{};

        //Find unique entries in raw_chunk

        //Create palette from unique entries

        //Convert and insert raw elements into chunk


        return {chunk, palette};
    }

}
