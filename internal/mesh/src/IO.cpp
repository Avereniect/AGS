//
// Created by avereniect on 5/18/22.
//
#include "ags/mesh/IO.hpp"

#include <ags/Logging.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace ags::mesh {

    Vertex_array read_vertex_array(std::string_view path) {
        static constexpr std::uint32_t position_loc = 0;
        static constexpr std::uint32_t normal_loc   = 1;
        static constexpr std::uint32_t uv_coord_loc = 2;

        Assimp::Importer importer{};

        const int process_flags =
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType;

        const aiScene* scene = importer.ReadFile(path.data(), process_flags);

        if (!scene) {
            AGS_ERROR(
                "{}\n {1}",
                AGS_CODE_LOCATION,
                "Failed to open file ",
                path
            );
            return {};
        }

        if (!scene->mNumMeshes) {
            AGS_NOTIFY("File {0} contained no meshes", path);
            return {};
        }
        const aiMesh* mesh = scene->mMeshes[0];

        if (!mesh->HasPositions()) {
            AGS_NOTIFY("The first mesh in file {0} had no position information", path);
            return {};
        }

        if (mesh->mNumVertices == 0) {
            AGS_NOTIFY("The first mesh in file {0} had zero vertices", path);
            return {};
        }

        Vertex_array ret{};

        //Read indices
        {
            std::uint32_t num_indices = mesh->mNumFaces * 3;

            std::vector<std::uint32_t> temp_buffer;
            temp_buffer.resize(num_indices);

            for (std::uint32_t i = 0; i < mesh->mNumFaces; ++i) {
                temp_buffer[3 * i + 0] = mesh->mFaces[i].mIndices[0];
                temp_buffer[3 * i + 1] = mesh->mFaces[i].mIndices[1];
                temp_buffer[3 * i + 2] = mesh->mFaces[i].mIndices[2];
            }

            ret.specify_indices(num_indices, temp_buffer.data());
        }

        //Read positions
        {
            std::vector<float> temp_buffer;
            temp_buffer.resize(mesh->mNumVertices * 3);

            for (int i = 0; i < mesh->mNumVertices; ++i) {
                temp_buffer[3 * i + 0] = mesh->mVertices[i][0];
                temp_buffer[3 * i + 1] = mesh->mVertices[i][1];
                temp_buffer[3 * i + 2] = mesh->mVertices[i][2];
            }

            ret.specify_attribute(position_loc, Attribute_width::THREE, temp_buffer.data());
        }

        //Read normals
        if (mesh->HasNormals()){
            std::vector<float> temp_buffer;
            temp_buffer.resize(mesh->mNumVertices * 3);

            for (int i = 0; i < mesh->mNumVertices; ++i) {
                temp_buffer[3 * i + 0] = mesh->mNormals[i][0];
                temp_buffer[3 * i + 1] = mesh->mNormals[i][1];
                temp_buffer[3 * i + 2] = mesh->mNormals[i][2];
            }

            ret.specify_attribute(normal_loc, Attribute_width::THREE, temp_buffer.data());
        }

        //Read UV coordinates
        if (mesh->HasTextureCoords(0)){
            std::vector<float> temp_buffer;
            temp_buffer.resize(mesh->mNumVertices * 2);

            for (int i = 0; i < mesh->mNumVertices; ++i) {
                temp_buffer[2 * i + 0] = mesh->mNormals[i][0];
                temp_buffer[2 * i + 1] = mesh->mNormals[i][1];
            }

            ret.specify_attribute(uv_coord_loc, Attribute_width::TWO, temp_buffer.data());
        }

        return ret;
    }

    Dynamic_vertex_array read_dynamic_vertex_array(const std::string& path) {
        using namespace Assimp;

        auto importer = Importer{};

        const aiScene* scene = importer.ReadFile(
            path.c_str(),
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType
        );

        if (!scene) {
            AGS_ERROR(
                "Error encountered at {0}\n {1}",
                AGS_CODE_LOCATION,
                "Failed to open file ",
                path.c_str()
            );
            return {};
        }

        Dynamic_vertex_array ret;

        if (!scene->mNumMeshes) {
            AGS_NOTIFY("File {0} contained no meshes", path.c_str());
            return {};
        }
        const aiMesh* mesh = scene->mMeshes[0];

        if (!mesh->HasPositions()) {
            AGS_NOTIFY("The first mesh in file {0} had no position information", path.c_str());
            return {};
        }

        if (mesh->mNumVertices == 0) {
            AGS_NOTIFY("The first mesh in file {0} had zero vertices", path.c_str());
            return {};
        }

        {
            std::uint32_t num_indices = mesh->mNumFaces * 3;

            std::vector<std::uint32_t> temp_buffer;
            temp_buffer.resize(num_indices);

            for (std::uint32_t i = 0; i < mesh->mNumFaces; ++i) {
                temp_buffer[3 * i + 0] = mesh->mFaces[i].mIndices[0];
                temp_buffer[3 * i + 1] = mesh->mFaces[i].mIndices[1];
                temp_buffer[3 * i + 2] = mesh->mFaces[i].mIndices[2];
            }

            ret.specify_indices(num_indices, temp_buffer.data());
        }

        {
            std::vector<float> temp_buffer;
            temp_buffer.resize(mesh->mNumVertices * 3);

            for (int i = 0; i < mesh->mNumVertices; ++i) {
                temp_buffer[3 * i + 0] = mesh->mVertices[i][0];
                temp_buffer[3 * i + 1] = mesh->mVertices[i][1];
                temp_buffer[3 * i + 2] = mesh->mVertices[i][2];
            }

            ret.specify_attribute("position", Attribute_width::THREE, temp_buffer.data());
        }

        if (mesh->HasNormals()){
            std::vector<float> temp_buffer;
            temp_buffer.resize(mesh->mNumVertices * 3);

            for (int i = 0; i < mesh->mNumVertices; ++i) {
                temp_buffer[3 * i + 0] = mesh->mNormals[i][0];
                temp_buffer[3 * i + 1] = mesh->mNormals[i][1];
                temp_buffer[3 * i + 2] = mesh->mNormals[i][2];
            }

            ret.specify_attribute("normal", Attribute_width::THREE, temp_buffer.data());
        }

        if (mesh->HasTextureCoords(0)){
            std::vector<float> temp_buffer;
            temp_buffer.resize(mesh->mNumVertices * 2);

            for (int i = 0; i < mesh->mNumVertices; ++i) {
                temp_buffer[2 * i + 0] = mesh->mNormals[i][0];
                temp_buffer[2 * i + 1] = mesh->mNormals[i][1];
            }

            ret.specify_attribute("uv0", Attribute_width::TWO, temp_buffer.data());
        }

        return ret;
    }

}
