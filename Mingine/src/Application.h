#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "API.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Components.h"
#include "Entity.h"
#include "Scene.h"

namespace Mingine {
	class API Application {
	public:
		Application();
		~Application();

		void Run();

		virtual void Update() {};
	private:
		static unsigned int m_Width;
		static unsigned int m_Height;

		static void windowSizeCallback(GLFWwindow* window, int width, int height);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	protected:
		static GLFWwindow* m_Window;
	};

	Application* CreateApplication();
}
