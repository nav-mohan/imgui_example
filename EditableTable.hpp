#ifndef EDITABLE_TABLE_HPP
#define EDITABLE_TABLE_HPP

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

class EditableTable
{
public:
    EditableTable(int rows, int cols);
    void Render();
private:
    int m_rows;
    int m_cols;
    std::vector<std::vector<std::string>> m_data;
    void AddRow(int rowIndex);
    void RemoveRow(int rowIndex);
};


#endif //EDITABLE_TABLE_HPP