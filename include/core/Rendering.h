#ifndef OUTSIDE_RENDERING_H
#define OUTSIDE_RENDERING_H
#include <glad/glad.h>
#include "../../include/core/Shaders.h"

class Rendering {
private:
    GLuint VAO, VBO, EBO;
    GLuint shaderProgram;

public:
    Rendering();
    ~Rendering();

    void setupBuffers(float vertices[], size_t verticesSize,
                      unsigned int indices[], size_t indicesSize) ;
    void useShader(int indexCount);
    void cleanup();
};

#endif //OUTSIDE_RENDERING_H