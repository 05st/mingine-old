#include "Renderer.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Components.h"

namespace Mingine {
	glm::vec4 Renderer::m_ClearColor = glm::vec4(0.2f, 0.3f, 0.4f, 1.0f);

	void Renderer::Prepare() {
		glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::DrawScene(Shader* shader, Scene* scene) {
		auto meshView = scene->m_Registry.view<MeshComponent, TransformComponent>();
		auto cameraView = scene->m_Registry.view<CameraComponent, TransformComponent>();

		shader->Bind();

		glm::mat4 proj = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 100.0f); // Default projection
		shader->SetMat4("projection", proj);
		shader->SetMat4("view", glm::mat4(1.0f)); // Default view

		for (auto [entity, cameraComponent, transformComponent] : cameraView.each()) {
			glm::vec3 pos = transformComponent.position;
			glm::vec3 rot = transformComponent.rotation;
			glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

			glm::vec3 front;
			front.x = cos(rot.y) * cos(rot.x);
			front.y = sin(rot.x);
			front.z = sin(rot.y) * cos(rot.x);
			front = glm::normalize(front);

			glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
			glm::vec3 up = glm::normalize(glm::cross(right, front));

			glm::mat4 view = glm::lookAt(pos, pos + front, up);

			shader->SetMat4("view", view);
			shader->SetMat4("projection", cameraComponent.camera.GetProjection());

			break;
		}

		for (auto [entity, meshComponent, transformComponent] : meshView.each()) {
			shader->SetMat4("transform", transformComponent.GetTransform());
			meshComponent.mesh.Draw();
		}

		shader->Unbind();
	}
}
