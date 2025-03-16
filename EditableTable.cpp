#include "EditableTable.hpp"

EditableTable::EditableTable(int rows, int cols) : m_rows(rows), m_cols(cols) {
    m_data.resize(m_rows, std::vector<std::string>(m_cols, ""));
}

void EditableTable::AddRow(int rowIndex) {
    if (rowIndex < 0 || rowIndex >= m_rows) return;
    m_data.insert(m_data.begin() + rowIndex + 1, std::vector<std::string>(m_cols, ""));
    m_rows++;
}

void EditableTable::RemoveRow(int rowIndex) {
    if (m_rows > 1 && rowIndex >= 0 && rowIndex < m_rows) {
        m_data.erase(m_data.begin() + rowIndex);
        m_rows--;
    }
}

void EditableTable::Render() {
    ImGui::Begin("Editable Table", nullptr, ImGuiWindowFlags_NoCollapse);

    if (ImGui::BeginTable("Table", m_cols + 1, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable)) {
        for (int i = 0; i < m_rows; i++) {
            ImGui::TableNextRow();
            for (int j = 0; j < m_cols; j++) {
                ImGui::TableNextColumn();
                ImGui::PushItemWidth(-FLT_MIN);

                char buffer[128];
                strncpy(buffer, m_data[i][j].c_str(), sizeof(buffer));
                buffer[sizeof(buffer) - 1] = '\0';

                if (ImGui::InputText(("##" + std::to_string(i) + "_" + std::to_string(j)).c_str(), buffer, sizeof(buffer))) {
                    m_data[i][j] = buffer;
                }
                ImGui::PopItemWidth();
            }

            // Add buttons in the last column
            ImGui::TableNextColumn();
            if (ImGui::Button(("+##" + std::to_string(i)).c_str())) {
                AddRow(i);
            }
            ImGui::SameLine();
            if (ImGui::Button(("-##" + std::to_string(i)).c_str())) {
                RemoveRow(i);
            }
        }
        ImGui::EndTable();
    }

    ImGui::End();
}
