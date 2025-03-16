#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <imgui.h>

class CsvTable {
private:
    std::vector<std::vector<std::string>> data = {{"1","2","3","4"},{"1","2","3","4"},{"1","2","3","4"}};
    std::string filename;
    int numColumns = 4;

public:
    CsvTable(const std::string& file) {
        filename = file;
        LoadCSV(file);
    }

    void LoadCSV(const std::string& file) {
        std::ifstream inFile(file);
        std::string line;
        // data.clear();

        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::vector<std::string> row;
            std::string cell;

            while (std::getline(ss, cell, ',')) {
                row.push_back(cell);
            }

            if (row.size() > numColumns) numColumns = row.size();
            data.push_back(row);

        }
        inFile.close();
        printf("%d\n",numColumns);

    }

    void SaveCSV() {
        std::ofstream outFile(filename);
        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                outFile << row[i];
                if (i < row.size() - 1) outFile << ",";
            }
            outFile << "\n";
        }
        outFile.close();
    }

    void RenderTable() {
        if (ImGui::Begin("CSV Table")) {
            if (ImGui::Button("Save CSV")) {
                SaveCSV();
            }

            if (ImGui::BeginTable("CSVTable", numColumns, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
                for (size_t row = 0; row < data.size(); ++row) {
                    // printf("ROW %d\n",row);
                    ImGui::TableNextRow();
                    for (size_t col = 0; col < data[row].size(); ++col) {
                        ImGui::TableSetColumnIndex(col);
                        
                        char buffer[256];
                        strncpy(buffer, data[row][col].c_str(), sizeof(buffer));
                        
                        if (ImGui::InputText(("##cell" + std::to_string(row) + "_" + std::to_string(col)).c_str(), buffer, sizeof(buffer))) {
                            data[row][col] = buffer;
                        }
                    }
                }
                ImGui::EndTable();
            }
        }
        ImGui::End();
    }
};
