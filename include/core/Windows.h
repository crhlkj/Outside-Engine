#ifndef OUTSIDE_WINDOWS_H
#define OUTSIDE_WINDOWS_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../editor/ImguiRender.h"
#include "../editor/PerformanceMonitor.h"

#include "../../include/core/Rendering.h"
#include "../../include/core/Shaders.h"

class Windows
{
private:
    GLFWwindow *window{};
    Rendering rendering;
    Shaders shaders;

    ImguiRender imguiRender;
    PerformanceMonitor fpsCounter;

public:
    Windows();
    ~Windows();

    static void setWindowIcon(GLFWwindow *window, const char *iconPath);
    void createWindow(int width, int height, const char *title);
    [[nodiscard]] bool running() const;
    void run_loop();
    [[nodiscard]] GLFWwindow *getWindow() const;
};

#endif // OUTSIDE_WINDOWS_H
