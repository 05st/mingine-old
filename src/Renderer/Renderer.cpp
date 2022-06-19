#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Components.h"

#include <iostream>

glm::vec4 Renderer::m_ClearColor = glm::vec4(0.2f, 0.3f, 0.4f, 1.0f);

void Renderer::Prepare() {
    glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::DrawScene(Scene* scene) {
    auto view = scene->m_Registry.view<MeshComponent>();

    for (auto [entity, meshComponent] : view.each()) {
        meshComponent.mesh.Draw();
    }
}