#ifndef APPLICATION_H
#define APPLICATION_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Application {
public:
    static void Init();
    static void Loop();
    static void Cleanup();

    static void Run();
private:
    static unsigned int m_Width, m_Height;
    static GLFWwindow* m_Window;

    static void windowSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif