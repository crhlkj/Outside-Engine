#ifndef OUTSIDE_RENDERING_H
#define OUTSIDE_RENDERING_H
#include <glad/glad.h>

class Rendering {
private:
    GLuint VAO, VBO, EBO;
    GLuint shaderProgram;
public:
    Rendering();
    ~Rendering();

    void setupBuffers(float vertices[], unsigned int indices[]);
    void useShader(GLuint shaderProgram);
    void cleanup();
};

#endif //OUTSIDE_RENDERING_H