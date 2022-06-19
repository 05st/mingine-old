#include "Application.h"

#include <iostream>

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"

unsigned int Application::m_Width = 800;
unsigned int Application::m_Height = 600;
GLFWwindow* Application::m_Window = nullptr;
Scene* Application::m_ActiveScene = nullptr;

void Application::Run() {
    Init();
    Loop();
    Cleanup();
}

void Application::Init() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        std::exit(0);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window
    m_Window = glfwCreateWindow(m_Width, m_Height, "Mingine", NULL, NULL);
    if (!m_Window) {
        glfwTerminate();
        std::cout << "Failed to create GLFW window" << std::endl;
        std::exit(0);
    }
    glfwMakeContextCurrent(m_Window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        std::cout << "Failed to initialize GLAD" << std::endl;
        std::exit(0);
    }

    glViewport(0, 0, m_Width, m_Height);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_Window, windowSizeCallback);
    glfwSetKeyCallback(m_Window, keyCallback);

    // Setup ImGui

    // Enable VSync
    glfwSwapInterval(1);

    // Test
    Shader* s = new Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    s->Bind();

    m_ActiveScene = new Scene();
    Entity e = m_ActiveScene->CreateEntity();
    e.AddComponent<MeshComponent>(Mesh("C:/Users/Sami/Documents/Projects/physicsengine/assets/zuball/zuball.obj"));
}

void Application::Cleanup() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Application::Loop() {
    while (!glfwWindowShouldClose(m_Window)) {
        Renderer::Prepare();
        Renderer::DrawScene(m_ActiveScene);

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Application::windowSizeCallback(GLFWwindow* window, int width, int height) {
    m_Width = (unsigned int)width;
    m_Height = (unsigned int)height;
    glViewport(0, 0, m_Width, m_Height);
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}