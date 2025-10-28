#ifndef OUTSIDE_RENDERING_H
#define OUTSIDE_RENDERING_H
#include <glad/glad.h>
#include "../../include/core/Shaders.h"

class Rendering
{
private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLuint shaderProgram;

public:
    Rendering();
    ~Rendering();

    void setupShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    void setupBuffers(float vertices[], size_t verticesSize, unsigned int indices[], size_t indicesSize);

    void drawRender(int elemets) const;
    void cleanup();
};

#endif // OUTSIDE_RENDERING_H