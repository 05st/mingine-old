#include <Mingine.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

class Editor : public Mingine::Application {
public:
	Editor() {
		// Test
		m_Shader = new Mingine::Shader("../../../Editor/shaders/vertex.glsl", "../../../Editor/shaders/fragment.glsl");

		m_ActiveScene = new Mingine::Scene();
		Mingine::Entity e = m_ActiveScene->CreateEntity();
		e.AddComponent<Mingine::MeshComponent>(Mingine::Mesh("../../../Editor/assets/backpack/backpack.obj"));
		e.GetComponent<Mingine::TransformComponent>().position = glm::vec3(0.0f, 0.0f, -5.0f);

		Mingine::Entity cam = m_ActiveScene->CreateEntity();
		cam.AddComponent<Mingine::CameraComponent>(glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 100.0f));
		cam.GetComponent<Mingine::TransformComponent>().position = glm::vec3(2.0f, 0.0f, 0.0f);
		cam.GetComponent<Mingine::TransformComponent>().rotation = glm::vec3(0.0f, -glm::pi<float>() / 2.0f, 0.0f);

		// Setup ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	~Editor() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Update() {
		Mingine::Renderer::DrawScene(m_Shader, m_ActiveScene);

		ImGui::Begin("Explorer");
		ImGui::Text("Entities");
		ImGui::End();
	}
private:
	// Testing
	Mingine::Shader* m_Shader;
	Mingine::Scene* m_ActiveScene;
};

Mingine::Application* Mingine::CreateApplication() {
	return new Editor();
}
