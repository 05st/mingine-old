#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <string>

#include "Renderer/Mesh.h"
#include "Camera.h"

struct TagComponent {
    std::string tag;
    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string tag) : tag(tag) {};
};

struct TransformComponent {
    glm::vec3 position = glm::vec3();
    glm::vec3 rotation = glm::vec3();
    glm::vec3 scale = glm::vec3(1.0f);

    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
    TransformComponent(const glm::vec3& position) : position(position) {}
};

struct CameraComponent {
    Camera camera;

    CameraComponent() = default;
    CameraComponent(const CameraComponent&) = default;
    CameraComponent(const glm::mat4& projection) : camera(projection) {}
};

struct MeshComponent {
    Mesh mesh;

    MeshComponent() = default;
    MeshComponent(const MeshComponent&) = default;
    MeshComponent(const Mesh mesh) : mesh(mesh) {}
};

#endif