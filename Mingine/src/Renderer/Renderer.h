#pragma once

#include <glm/glm.hpp>

#include "Shader.h"
#include "../Scene.h"

namespace Mingine {
	class Renderer {
	public:
		static void Prepare();
		static void DrawScene(Shader* shader, Scene* scene);
	private:
		static glm::vec4 m_ClearColor;
	};
}
