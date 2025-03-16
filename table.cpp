#include "table.hpp"

static char userText[128] = "Hello, ImGui!";  // Text buffer for input field
static float sliderValue = 0.5f;              // A slider-controlled value
static float bgColor[3] = {0.2f, 0.3f, 0.3f}; // Background color

void Table::Init(GLFWwindow* window, const char* glsl_version){
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplGlfw_InitForOpenGL(window,true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGui::StyleColorsLight();
}

void Table::Update() 
{
    ImGui::Begin("Interactive Table");

    // Input field to add new numbers
	ImGui::PushItemWidth(150);
    ImGui::InputFloat("New Value", &newValue);
    ImGui::SameLine();
    if (ImGui::Button("Add"))
	{
        values.push_back(newValue);
        newValue = 0.0f;  // Reset input
    }

    // Table UI
    if (ImGui::BeginTable("ValuesTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) 
	{
        ImGui::TableSetupColumn("Index");
        ImGui::TableSetupColumn("Value");
        ImGui::TableHeadersRow();

        for (size_t i = 0; i < values.size(); ++i) 
		{
            ImGui::TableNextRow();

            // Column 1: Index
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%d", (int)i);

            // Column 2: Editable Value
            ImGui::TableSetColumnIndex(1);
            ImGui::PushID(i);  // Unique ID for each row
            ImGui::SetNextItemWidth(-1);
            ImGui::InputFloat("##Value", &values[i]);
            ImGui::PopID();

            // Click to select row
            if (ImGui::IsItemClicked()) 
			{
                selectedRow = i;
            }
        }
        ImGui::EndTable();
    }

    // Remove selected row
    if (selectedRow >= 0 && ImGui::Button("Remove Selected")) 
	{
        values.erase(values.begin() + selectedRow);
        selectedRow = -1;  // Reset selection
    }

    ImGui::End();
}

// feed inputs to dearIMGUI, start a new frame
void Table::NewFrame(){
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Table::Render(){
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Table::Shutdown(){
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}