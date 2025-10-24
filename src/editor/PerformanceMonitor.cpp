#include "../../include/editor/PerformanceMonitor.h"

PerformanceMonitor::PerformanceMonitor()
{
    this->fps = 0.0f;
    this->lastTime = glfwGetTime();
}

void PerformanceMonitor::Update()
{
    double currentTime = glfwGetTime();
    double frameTime = currentTime - lastTime;
    fps = 1.0f / frameTime;
    lastTime = currentTime;
}

void PerformanceMonitor::Render()
{
    ImGui::Begin("Performance", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("FPS: %.2f", fps);
    ImGui::End();
}

float PerformanceMonitor::getFPS()
{
    return fps;
}