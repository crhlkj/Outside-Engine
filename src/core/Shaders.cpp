#include "../../include/core/Shaders.h"

#include <fstream>
#include <sstream>

Shaders::Shaders() : vertexShader(0), fragmentShader(0), ID(0) {}

Shaders::~Shaders() {
    cleanup();
}

bool Shaders::loadShader(const std::string& pathFile, std::string& shaderSource) {
    std::ifstream file(pathFile);
    if (!file.is_open()) {
        std::cerr << "ERROR: Failed to open shader file: " << pathFile << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    shaderSource = buffer.str();
    file.close();

    return true;
}

bool Shaders::compileShader(const GLenum type, const std::string &shaderSource, GLuint &shaderID) {
    shaderID = glCreateShader(type);
    const char* src = shaderSource.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);

    return compileError(shaderID, "SHADER");
}

bool Shaders::linkShaders() {
    if (vertexShader == 0 || fragmentShader == 0) {
        std::cerr << "ERROR: Shaders not compiled before linking" << std::endl;
        return false;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    return compileError(ID, "PROGRAM");
}

void Shaders::use() const {
    if (ID != 0) {
        glUseProgram(ID);
    }
}

void Shaders::cleanup() {
    if (vertexShader != 0) {
        glDeleteShader(vertexShader);
        vertexShader = 0;
    }
    if (fragmentShader != 0) {
        glDeleteShader(fragmentShader);
        fragmentShader = 0;
    }
    if (ID != 0) {
        glDeleteProgram(ID);
        ID = 0;
    }
}

bool Shaders::compileError(const GLuint shader, const std::string& type) {
    int success;
    char infoLog[1024];

    if (type == "SHADER") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            return false;
        }
    } else if (type == "PROGRAM") {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            return false;
        }
    }

    return true;
}
