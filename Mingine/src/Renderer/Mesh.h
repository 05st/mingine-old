#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Mingine {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
    };

    class SubMesh {
    public:
        SubMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

        void Draw();
    private:
        unsigned int m_VAO, m_VBO, m_EBO;

        std::vector<Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;

        void setup();
    };

    class Mesh {
    public:
        Mesh(std::string path);
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices); // For only one submesh

        void Draw();
    private:
        std::vector<SubMesh> m_SubMeshes;

        void processNode(aiNode* node, const aiScene* scene);
        SubMesh processSubMesh(aiMesh* mesh, const aiScene* scene);
    };
}
