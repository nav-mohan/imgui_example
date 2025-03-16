#include "EditableTable.hpp"
#include "ClockWindow.hpp"
#include "CSVTable.hpp"

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <vector>
extern "C" {
    #include <libavformat/avformat.h>
    #include <libavdevice/avdevice.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/opt.h>
    #include <libswresample/swresample.h>
}
#define AUDIO_DEVICE "pulse"
#define SAMPLE_RATE 44100
#define CHANNELS 2
#define FORMAT AV_SAMPLE_FMT_S16

void write_wav_header(std::ofstream &file, int sample_rate, int num_channels, int num_samples) {
    int byte_rate = sample_rate * num_channels * 2;
    int data_size = num_samples * num_channels * 2;

    file.write("RIFF", 4);
    int chunk_size = 36 + data_size;
    file.write(reinterpret_cast<const char *>(&chunk_size), 4);
    file.write("WAVE", 4);

    file.write("fmt ", 4);
    int subchunk1_size = 16;
    short audio_format = 1;
    file.write(reinterpret_cast<const char *>(&subchunk1_size), 4);
    file.write(reinterpret_cast<const char *>(&audio_format), 2);
    file.write(reinterpret_cast<const char *>(&num_channels), 2);
    file.write(reinterpret_cast<const char *>(&sample_rate), 4);
    file.write(reinterpret_cast<const char *>(&byte_rate), 4);
    short block_align = num_channels * 2;
    file.write(reinterpret_cast<const char *>(&block_align), 2);
    short bits_per_sample = 16;
    file.write(reinterpret_cast<const char *>(&bits_per_sample), 2);

    file.write("data", 4);
    file.write(reinterpret_cast<const char *>(&data_size), 4);
}

const char* glsl_version = "#version 330";
void SetupGLFW() 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Cleanup(GLFWwindow* window) 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void SetupImGuiStyleAndFont() {
    ImGuiIO& io = ImGui::GetIO();
    
    // Load a larger font (e.g., 20px)
    if(io.Fonts->AddFontFromFileTTF("../fonts/ITCAvantGardeStd-Bk.otf", 20.0f))
        ImGui_ImplOpenGL3_CreateFontsTexture();
}

int main()
{
    SetupGLFW();
    GLFWwindow * window = glfwCreateWindow(800,600, "ImGui app", nullptr,nullptr);
    if(window == NULL) {printf("Failed to initialize window\n"); glfwTerminate();}
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL();
    printf("LOADED gladLoadGL()\n");

    avformat_network_init();
    avdevice_register_all();
    std::cout << "FFmpeg initialized successfully!\n";

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    EditableTable table(5,3);
    ClockWindow clock;
    CsvTable csvtable("data.csv");

    SetupImGuiStyleAndFont();

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        table.Render();
        clock.Render();
        csvtable.RenderTable();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0,0,display_w,display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    Cleanup(window);
    return 0;
}