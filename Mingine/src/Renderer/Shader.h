#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

namespace Mingine {
	class Shader {
	public:
		Shader(std::string vertexShaderSource, std::string fragmentShaderSource);
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Shader();

		void Bind();
		void Unbind();

		void SetMat4(const std::string& name, const glm::mat4& mat) const {
			glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
	private:
		unsigned int m_ShaderProgram;

		unsigned int createShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource);
		unsigned int compileShader(std::string source, unsigned int shaderType);

		std::string readFile(std::string filePath);
	};
}
