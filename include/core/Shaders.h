#ifndef OUTSIDE_SHADERS_H
#define OUTSIDE_SHADERS_H

#include <iostream>
#include <string>
#include <glad/glad.h>


class Shaders {
private:
    GLuint vertexShader, fragmentShader;
    std::string vertexSource, fragmentSource;
    GLuint ID;

public:
    Shaders();
    ~Shaders();

    static bool loadShader(const std::string& pathFile, std::string& shaderSource);
    bool compileShader(GLenum type, const std::string& shaderSource, GLuint& shaderID);
    bool linkShaders();
    void use() const;
    void cleanup();
    GLuint getID() const { return ID; }

private:
    static bool compileError(GLuint shader, const std::string& type);
};


#endif //OUTSIDE_SHADERS_H