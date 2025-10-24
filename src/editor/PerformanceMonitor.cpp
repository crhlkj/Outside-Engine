#include "../../include/editor/PerformanceMonitor.h"

PerformanceMonitor::PerformanceMonitor()
{
    this->fps = 0.0f;
    this->frameTime = 0.0f;
    this->frameCount = 0;
    this->lastTime = glfwGetTime();
    this->averageFPS = 0.0f;
    this->minFPS = FLT_MAX;
    this->maxFPS = 0.0f;
}

void PerformanceMonitor::Init()
{
    this->frameCount = 0;
    this->lastTime = glfwGetTime();
    this->averageFPS = 0.0f;
    this->minFPS = FLT_MAX;
    this->maxFPS = 0.0f;
}

void PerformanceMonitor::Update()
{
    double currentTime = glfwGetTime();
    frameTime = currentTime - lastTime;
    fps = 1.0f / frameTime;
    lastTime = currentTime;

    frameCount++;

    if (fps < minFPS)
    {
        minFPS = fps;
    }
    if (fps > maxFPS)
    {
        maxFPS = fps;
    }

    if (averageFPS == 0.0f)
    {
        averageFPS = fps;
    }
    else
    {
        averageFPS = 0.1f * fps + 0.9f * averageFPS;
    }
}

void PerformanceMonitor::Render()
{
    ImGui::Begin("Performance", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Average FPS: %.2f", averageFPS);
    ImGui::Text("Current FPS: %.2f", fps);
    ImGui::Text("------------------");
    ImGui::Text("Min FPS: %.2f", minFPS);
    ImGui::Text("Max FPS: %.2f", maxFPS);
    ImGui::Text("------------------");
    ImGui::Text("Frame Time: %.4f ms", frameTime * 1000.0f);
    ImGui::End();
}

float PerformanceMonitor::getFPS()
{
    return averageFPS;
}