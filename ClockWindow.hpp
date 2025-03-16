#ifndef CLOCK_WINDOW_HPP
#define CLOCK_WINDOW_HPP

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ctime>
#include <chrono>

class ClockWindow
{
public:
    void Render();
};


#endif // CLOCK_WINDOW_HPP