#include "ClockWindow.hpp"

void ClockWindow::Render()
{
    ImGui::Begin("Clock Window");
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    ImGui::Text("Current Time: %s",std::ctime(&now_c));
    ImGui::End();
}