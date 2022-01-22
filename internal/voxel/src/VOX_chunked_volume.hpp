//
// Created by avereniect on 12/6/21.
//

#ifndef AGS_VOX_CHUNKED_VOLUME_HPP
#define AGS_VOX_CHUNKED_VOLUME_HPP

#include <cstdint>
#include "aul/containers/Matrix.hpp"

namespace ags::voxel {

    using voxel_type = std::uint32_t;

    static constexpr std::uint32_t chunk_size = 8;

    using Raw_chunk = aul::Matrix<voxel_type, 3>;

    class Chunk_palette {
    public:

    private:

        //=================================================
        // Instance members
        //=================================================

        ///
        /// TODO: Use custom allocator
        ///
        std::vector<std::uint32_t> mappings;

    };

    ///
    ///
    ///
    class Chunk {
    public:

        Chunk();
        ~Chunk();

    private:

        

    };

    ///
    /// A representation of a volume which is
    ///
    class Chunked_volume {
    public:

        //=================================================
        // Type aliases
        //=================================================

        //=================================================
        // -ctors
        //=================================================

        Chunked_volume();
        Chunked_volume(const Chunked_volume&);
        Chunked_volume(Chunked_volume&&);
        ~Chunked_volume();

        //=================================================
        // Assignment operators
        //=================================================

        Chunked_volume& operator=(const Chunked_volume&);
        Chunked_volume& operator=(Chunked_volume&&);

    private:

        //=================================================
        // Instance members
        //=================================================

        aul::Matrix<std::unique_ptr<Chunk>, 3> matrix;

        //=================================================
        // Helper functions
        //=================================================

    };

    Raw_chunk decompress(const Chunk&);

    std::tuple<Chunk, Chunk_palette> compress(const Raw_chunk&);

}

#endif //AGS_VOX_CHUNKED_VOLUME_HPP
