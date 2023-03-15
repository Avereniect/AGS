#include "Mesh.hpp"

namespace ags::are::vk_kernel {

    /*
    void Mesh::load(const ags::mesh::Fixed_vertex_array_view& mesh) {

    }
    */

    //=====================================================
    // -ctors
    //=====================================================

    //Mesh::Mesh(Mesh&& mesh) noexcept {}

    Mesh::~Mesh() {
        unload();
    }

    //=====================================================
    // Assignment operators
    //=====================================================

    //Mesh& Mesh::operator=(Mesh&& mesh) noexcept {return *this;}

    //=====================================================
    // Buffer mutators
    //=====================================================

    void Mesh::load(const mesh::Vertex_array& mesh) {
        //TODO: Implement
    }

    /*
    void Mesh::load(mesh::Dynamic_vertex_array& mesh) {
        //TODO: Implement
    }
    */

    void Mesh::unload() {
        //TODO: Implement
    }

    //=====================================================
    // Accessors
    //=====================================================

    std::uint32_t Mesh::index_count() const {
        return num_indices;
    }

    std::uint32_t Mesh::vertex_count() const {
        return num_vertices;
    }

    aul::Span<const std::uint32_t> Mesh::attribute_locations() const {
        return attributes.keys();
    }

    Attribute_type Mesh::attribute_type(std::uint32_t loc) const {
        auto it = attributes.find(loc);
        if (it == attributes.end()) {
            return Attribute_type::NULL_ATTRIBUTE_TYPE;
        } else {
            return aul::get<1>(it)->type;
        }
    }

    std::vector<vk::VertexInputAttributeDescription>
    Mesh::create_attribute_descriptions(const mesh::Vertex_array& mesh) {
        std::vector<vk::VertexInputAttributeDescription> ret;

        for (auto& loc : mesh.attribute_locations()) {
            const auto& attrib = mesh.get_attribute(loc);

            Attribute_type type_enum = to_attribute_type(attrib.type(), attrib.width());


            vk::VertexInputAttributeDescription desc{
                loc,
                0, //Binding location
                to_native_enum(type_enum),
                0 //offset
            };

            ret.emplace_back();
        }

        return ret;
    }

}
