#include "../../include/core/Rendering.h"
#include "../../include/core/Shaders.h"
#include <glad/glad.h>

Shaders shaders;

Rendering::Rendering() : VAO(0), VBO(0), EBO(0), shaderProgram(0) {}
Rendering::~Rendering() {
    cleanup();
}

// std::string vertexSource;
// if (shader.loadShader("vertex.glsl", vertexSource)) {
//     shader.compileShader(GL_VERTEX_SHADER, vertexSource, shader.vertexShader);
// }
//
// // Load and compile fragment shader
// std::string fragmentSource;
// if (shader.loadShader("fragment.glsl", fragmentSource)) {
//     shader.compileShader(GL_FRAGMENT_SHADER, fragmentSource, shader.fragmentShader);
// }
//
// // Link shaders and use
// if (shader.linkShaders()) {
//     shader.use();
// }

void Rendering::setupBuffers(float vertices[], unsigned int indices[]) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Rendering::useShader(GLuint shaderProgram) {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
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
