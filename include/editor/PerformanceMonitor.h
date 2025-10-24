#ifndef OUTSIDE_FPS_RENDERING_H
#define OUTSIDE_FPS_RENDERING_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

class PerformanceMonitor
{
private:
    float fps;
    double lastTime;

public:
    PerformanceMonitor();
    void Update();
    void Render();
    float getFPS();
};

#endif // OUTSIDE_FPS_RENDERING_H
