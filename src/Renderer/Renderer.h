#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

#include "../Scene.h"

class Renderer {
public:
    static void Prepare();
    static void DrawScene(Scene* scene);
private:
    static glm::vec4 m_ClearColor;
};

#endif