//
// Created by avereniect on 1/9/22.
//
#include "Mesh.hpp"
#include "Mesh_kernel.hpp"
#include "Enums.hpp"

#include <ags/Logging.hpp>

namespace ags::are::gl_kernel {

    //=====================================================
    // -ctors
    //=====================================================

    Mesh::Mesh(Mesh&& mesh) noexcept:
        Object(std::move(mesh)),
        ibo_id(std::exchange(mesh.ibo_id, 0)),
        num_indices(std::exchange(mesh.num_indices, 0)),
        num_vertices(std::exchange(mesh.num_vertices, 0)),
        attributes(std::exchange(mesh.attributes, {})) {}

    Mesh::~Mesh() {
        unload();
    }

    //=====================================================
    // Assignment operators
    //=====================================================

    Mesh& Mesh::operator=(Mesh&& rhs) noexcept {
        ibo_id = std::exchange(rhs.ibo_id, 0);
        num_indices = std::exchange(rhs.num_indices, 0);
        num_vertices = std::exchange(rhs.num_vertices, 0);
        attributes = std::exchange(rhs.attributes, {});
        Object::operator=(std::move(rhs));

        return *this;
    }

    //=====================================================
    // Buffer mutators
    //=====================================================

    void Mesh::load(const mesh::Vertex_array& vertex_array) {
        if (Mesh_kernel::max_vertex_attribute_count() < vertex_array.attributes().size()) {
            AGS_ERROR("Vertex_array parameter has more attributes than supported.");
            return;
        }

        //TODO: Input verification
        // Reject attributes whose types aren't int32, uint32, or float32

        if (id) {
            Mesh_kernel::release_vbo(ibo_id);
            Mesh_kernel::release_vao(id);
        }

        ibo_id = Mesh_kernel::acquire_vbo();
        id = Mesh_kernel::acquire_vao();
        glBindVertexArray(id);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
        auto index_buffer_size = sizeof(std::uint32_t) * vertex_array.index_count();
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            index_buffer_size,
            vertex_array.indices().data(),
            GL_STATIC_DRAW
        );

        if (glGetError() == GL_OUT_OF_MEMORY) {
            unload();
            AGS_ERROR("Not enough GPU memory available to load mesh data.");
            return;
        }

        num_indices = vertex_array.index_count();
        num_vertices = vertex_array.vertex_count();

        auto locations = vertex_array.attribute_locations();
        for (auto loc : locations) {
            const auto& src_attribute = vertex_array.get_attribute(loc);

            Attribute local_attribute{
                Mesh_kernel::acquire_vbo(),
                are::to_attribute_type(src_attribute.primitive, src_attribute.width())
            };

            GLsizeiptr attribute_buffer_size =
                size_of_attribute_type(local_attribute.type) *
                vertex_array.vertex_count();

            const float* tmp_ptr = reinterpret_cast<const float*>(src_attribute.ptr);

            glBindBuffer(GL_ARRAY_BUFFER, local_attribute.handle);
            glBufferData(GL_ARRAY_BUFFER, attribute_buffer_size, src_attribute.ptr, GL_STATIC_DRAW);

            if (glGetError() == GL_OUT_OF_MEMORY) {
                unload();
                AGS_ERROR("Not enough GPU memory available to load mesh data.");
                return;
            }

            glVertexAttribPointer(loc, GLint(src_attribute.width()), to_native_enum(src_attribute.type()), false, 0, nullptr);
            glEnableVertexAttribArray(loc);

            attributes.emplace(loc, local_attribute);
        }
    }

    void Mesh::unload() {
        //TODO: Defer to mesh kernel
        glDeleteVertexArrays(1, &id);
        glDeleteBuffers(1, &id);

        for (auto attrib : attributes.values()) {
            glDeleteBuffers(1, &attrib.handle);
        }

        id = 0;
        ibo_id = 0;
        num_indices = 0;
        num_vertices = 0;
        attributes = {};
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

}
