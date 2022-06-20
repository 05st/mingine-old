#include "Mesh.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Mingine {
    // Mesh
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
        m_SubMeshes.push_back(SubMesh(vertices, indices));
    }

    Mesh::Mesh(std::string path) {
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "Failed to load model: " << import.GetErrorString() << std::endl;
            return;
        }

        processNode(scene->mRootNode, scene);
    }

    void Mesh::processNode(aiNode* node, const aiScene* scene) {
        for (int i = 0; i < node->mNumMeshes; i++)
            m_SubMeshes.push_back(processSubMesh(scene->mMeshes[node->mMeshes[i]], scene));

        for (int i = 0; i < node->mNumChildren; i++)
            processNode(node->mChildren[i], scene);
    }

    SubMesh Mesh::processSubMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        // Vertices
        for (int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vert;
            glm::vec3 vec3;
            glm::vec2 vec2;

            vec3.x = mesh->mVertices[i].x;
            vec3.y = mesh->mVertices[i].y;
            vec3.z = mesh->mVertices[i].z;
            vert.position = vec3;

            vec3.x = mesh->mNormals[i].x;
            vec3.y = mesh->mNormals[i].y;
            vec3.z = mesh->mNormals[i].z;
            vert.normal = vec3;

            if (mesh->mTextureCoords[0]) {
                vec2.x = mesh->mTextureCoords[0][i].x;
                vec2.y = mesh->mTextureCoords[0][i].y;
            }
            vert.texCoord = vec2;

            vertices.push_back(vert);
        }

        // Indices
        for (int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        return SubMesh(vertices, indices);
    }

    void Mesh::Draw() {
        for (SubMesh submesh : m_SubMeshes) {
            submesh.Draw();
        }
    }

    // SubMesh
    SubMesh::SubMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : m_Vertices(vertices), m_Indices(indices) {
        setup();
    }

    void SubMesh::setup() {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), m_Indices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

        glBindVertexArray(0);
    }

    void SubMesh::Draw() {
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}