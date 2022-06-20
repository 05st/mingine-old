#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace Mingine {
    std::string Shader::readFile(std::string filePath) {
        std::ifstream ifs;
        ifs.open(filePath);

        std::stringstream stream;
        stream << ifs.rdbuf();
        ifs.close();

        return stream.str();
    }

    Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
        std::string vertexShaderSource = this->readFile(vertexShaderPath);
        std::string fragmentShaderSource = this->readFile(fragmentShaderPath);

        m_ShaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    }

    Shader::Shader(std::string vertexShaderSource, std::string fragmentShaderSource) {
        m_ShaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    }

    Shader::~Shader() {
        glDeleteProgram(m_ShaderProgram);
    }

    unsigned int Shader::createShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource) {
        unsigned int vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
        unsigned int fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        unsigned int program = glCreateProgram();

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        int success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(program, 512, nullptr, infoLog);

            glDeleteProgram(program);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            std::cout << infoLog;
            std::cout << "Failed to link shader program " << program << ": " << infoLog << std::endl;
            return 0;
        }

        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);

        return program;
    }

    unsigned int Shader::compileShader(std::string source, unsigned int shaderType) {
        unsigned int shader = glCreateShader(shaderType);

        const char* source_cstr = source.c_str();
        glShaderSource(shader, 1, &source_cstr, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);

            std::string shaderTypeName;
            switch (shaderType) {
            case GL_VERTEX_SHADER:
                shaderTypeName = "VertexShader";
                break;
            case GL_FRAGMENT_SHADER:
                shaderTypeName = "FragmentShader";
                break;
            }

            std::cout << "Failed to compile shader " << shaderTypeName << ": " << infoLog << std::endl;
            return 0;
        }

        return shader;
    }

    void Shader::Bind() {
        glUseProgram(m_ShaderProgram);
    }

    void Shader::Unbind() {
        glUseProgram(0);
    }
}
