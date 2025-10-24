#include "../../include/core/Rendering.h"
#include "../../include/core/Shaders.h"
#include <glad/glad.h>

Shaders shaders;

Rendering::Rendering() : VAO(0), VBO(0), EBO(0), shaderProgram(0) {
    std::string vertexSource;
    GLuint vertexShader = 0;
    if (shaders.loadShader("vertex.glsl", vertexSource)) {
        shaders.compileShader(GL_VERTEX_SHADER, vertexSource, vertexShader);
    }

    std::string fragmentSource;
    GLuint fragmentShader = 0;
    if (shaders.loadShader("fragment.glsl", fragmentSource)) {
        shaders.compileShader(GL_FRAGMENT_SHADER, fragmentSource, fragmentShader);
    }

    if (shaders.linkShaders()) {
        shaders.use();
        shaderProgram = shaders.getID();
    } else {
        cleanup();
    }
}
Rendering::~Rendering() {
    cleanup();
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

void Rendering::useShader(int indexCount) {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}


void Rendering::cleanup() {
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (EBO != 0) {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }
    if (shaderProgram != 0) {
        glDeleteProgram(shaderProgram);
        shaderProgram = 0;
    }
}