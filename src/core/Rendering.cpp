#include "../../include/core/Rendering.h"
#include "../../include/core/Shaders.h"
#include <glad/glad.h>

Shaders shaders;

Rendering::Rendering() : VAO(0), VBO(0), EBO(0), shaderProgram(0) { }
Rendering::~Rendering() { cleanup(); }

void Rendering::setupShader(std::string vertexShaderSource, std::string fragmentShaderSource, const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
    if (Shaders::loadShader(vertexShaderPath, vertexShaderSource))
    {
        GLuint vertexShader = 0;
        shaders.compileShader(GL_VERTEX_SHADER, vertexShaderSource, vertexShader);
    }

    if (Shaders::loadShader(fragmentShaderPath, fragmentShaderSource))
    {
        GLuint fragmentShader = 0;
        shaders.compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource, fragmentShader);
    }

    if (shaders.linkShaders())
    {
        shaders.use();
        shaderProgram = shaders.getID();
    }
    else
    {
        cleanup();
    }
}
void Rendering::setupBuffers(float vertices[], size_t verticesSize,
                            unsigned int indices[], size_t indicesSize) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Rendering::useShader(int indexCount) const
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void Rendering::cleanup()
{
    if (VAO != 0)
    {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    if (VBO != 0)
    {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (EBO != 0)
    {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }
    if (shaderProgram != 0)
    {
        glDeleteProgram(shaderProgram);
        shaderProgram = 0;
    }
}
