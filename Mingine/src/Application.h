#pragma once

#ifdef BUILD_DLL
	#define API __declspec(dllexport)
#else
	#define API __declspec(dllimport)
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

		static void Run();
	private:
		static unsigned int m_Width;
		static unsigned int m_Height;
		static GLFWwindow* m_Window;

		static void windowSizeCallback(GLFWwindow* window, int width, int height);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		// Testing
		static Scene* m_ActiveScene;
		static Shader* m_Shader;
	};

	Application* CreateApplication();
}
