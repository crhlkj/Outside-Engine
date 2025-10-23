#ifndef OUTSIDE_WINDOWS_H
#define OUTSIDE_WINDOWS_H

#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "../editor/ImguiRender.h"
#include "../editor/PerformanceMonitor.h"

class Windows {
private:
    GLFWwindow *window{};
    ImguiRender imguiRender;
    PerformanceMonitor fpsCounter;

public:
    Windows();
    ~Windows();
    void setWindowIcon(GLFWwindow *window, const char *iconPath);
    void createWindow(int width, int height, const char *title);
    [[nodiscard]] bool running() const;
    void run_loop();
    [[nodiscard]] GLFWwindow *getWindow() const;
};

#endif //OUTSIDE_WINDOWS_H
