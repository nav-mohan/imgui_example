#ifndef TABLE_H
#define TABLE_H

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

class Table {
public:
    void Init(GLFWwindow* window, const char* glsl_version);
    void NewFrame();
    void Update();
    void Render();
    void Shutdown();

private:
    std::vector<float> values;  // Stores table values
    int selectedRow = -1;       // Tracks selected row
    float newValue = 0.0f;      // New value input
};

#endif // TABLE_H
