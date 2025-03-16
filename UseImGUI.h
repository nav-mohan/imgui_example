#ifndef USEIMGUI_H
#define USEIMGUI_H

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

class UseImGui {
public:
    void Init(GLFWwindow* window, const char* glsl_version);
    void NewFrame();
    void Update();
    void Update3();
    void Render();
    void Shutdown();

private:
    std::vector<float> values;  // Stores table values
    int selectedRow = -1;       // Tracks selected row
    float newValue = 0.0f;      // New value input
};

#endif // USEIMGUI_H
