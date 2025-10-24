#ifndef OUTSIDE_IMGUIRENDER_H
#define OUTSIDE_IMGUIRENDER_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class ImguiRender
{
private:
    GLFWwindow *window;
    const char *glsl_version;

public:
    bool Initialize(GLFWwindow *window);
    void BeginFrame();
    void Shutdown();
    void EndFrame();
};

#endif // OUTSIDE_IMGUIRENDER_H