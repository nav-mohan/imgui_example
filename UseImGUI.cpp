#include "UseImGUI.h"

static char userText[128] = "Hello, ImGui!";  // Text buffer for input field
static float sliderValue = 0.5f;              // A slider-controlled value
static float bgColor[3] = {0.2f, 0.3f, 0.3f}; // Background color

void render_conan_logo()
{
	ImDrawList *draw_list = ImGui::GetWindowDrawList();
	float sz = 300.0f;
	static ImVec4 col1 = ImVec4(68.0 / 255.0, 83.0 / 255.0, 89.0 / 255.0, 1.0f);
	static ImVec4 col2 = ImVec4(40.0 / 255.0, 60.0 / 255.0, 80.0 / 255.0, 1.0f);
	static ImVec4 col3 = ImVec4(50.0 / 255.0, 65.0 / 255.0, 82.0 / 255.0, 1.0f);
	static ImVec4 col4 = ImVec4(20.0 / 255.0, 40.0 / 255.0, 60.0 / 255.0, 1.0f);
	const ImVec2 p = ImGui::GetCursorScreenPos();
	float x = p.x + 4.0f, y = p.y + 4.0f;
	draw_list->AddQuadFilled(ImVec2(x, y + 0.25 * sz), ImVec2(x + 0.5 * sz, y + 0.5 * sz), ImVec2(x + sz, y + 0.25 * sz), ImVec2(x + 0.5 * sz, y), ImColor(col1));
	draw_list->AddQuadFilled(ImVec2(x, y + 0.25 * sz), ImVec2(x + 0.5 * sz, y + 0.5 * sz), ImVec2(x + 0.5 * sz, y + 1.0 * sz), ImVec2(x, y + 0.75 * sz), ImColor(col2));
	draw_list->AddQuadFilled(ImVec2(x + 0.5 * sz, y + 0.5 * sz), ImVec2(x + sz, y + 0.25 * sz), ImVec2(x + sz, y + 0.75 * sz), ImVec2(x + 0.5 * sz, y + 1.0 * sz), ImColor(col3));
	draw_list->AddLine(ImVec2(x + 0.75 * sz, y + 0.375 * sz), ImVec2(x + 0.75 * sz, y + 0.875 * sz), ImColor(col4));
    draw_list->AddBezierCubic(ImVec2(x + 0.72 * sz, y + 0.24 * sz), ImVec2(x + 0.68 * sz, y + 0.15 * sz), ImVec2(x + 0.48 * sz, y + 0.13 * sz), ImVec2(x + 0.39 * sz, y + 0.17 * sz), ImColor(col4), 10, 18);
    draw_list->AddBezierCubic(ImVec2(x + 0.39 * sz, y + 0.17 * sz), ImVec2(x + 0.2 * sz, y + 0.25 * sz), ImVec2(x + 0.3 * sz, y + 0.35 * sz), ImVec2(x + 0.49 * sz, y + 0.38 * sz), ImColor(col4), 10, 18);
}


void UseImGui::Init(GLFWwindow* window, const char* glsl_version){
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplGlfw_InitForOpenGL(window,true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGui::StyleColorsLight();
}

void UseImGui::Update()
{
    render_conan_logo();

	ImGui::Begin("My First IMGUI Window");
	ImGui::InputText("Text BOx", userText, IM_ARRAYSIZE(userText));
	ImGui::Text("You typed %s",userText);
	ImGui::SliderFloat("slider", &sliderValue, 0.0f, 1.0f);
	ImGui::Text("Slider Value %.2f",sliderValue);
	ImGui::ColorEdit3("Background color",bgColor);
	if(ImGui::Button("Reset"))
	{
		sliderValue = 0.5f;
		bgColor[0] = 0.2f;
		bgColor[1] = 0.3f;
		bgColor[2] = 0.3f;
	}
	ImGui::End(); // "My First IMGUI Window"


	ImGui::Begin("My Second Window");
	ImGui::InputText("Text BOx", userText, IM_ARRAYSIZE(userText));
	ImGui::Text("You typed %s",userText);
	ImGui::SliderFloat("slider", &sliderValue, 0.0f, 1.0f);
	ImGui::Text("Slider Value %.2f",sliderValue);
	ImGui::ColorEdit3("Background color",bgColor);
	if(ImGui::Button("Reset"))
	{
		sliderValue = 0.5f;
		bgColor[0] = 0.2f;
		bgColor[1] = 0.3f;
		bgColor[2] = 0.3f;
	}
	ImGui::End(); // My Second Window
}

void UseImGui::Update3()
{
    static float f = 0.0f;
    static int counter1 = 0;
    static int counter2 = 0;

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::Text("This is some useful text");

    static float clear_color[3];
    ImGui::ColorEdit3("clear color", (float*)&clear_color);

    if(ImGui::Button("Button"))
		printf("counter1 = %d\n",counter1++);

    ImGui::SameLine();
	if (ImGui::Button("Begin-Recording")){
		counter2++;
		printf("\nAKSJKASKJA");
	}
    ImGui::Text("Counter = %d Counter = %d",counter1,counter2);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",1000.0f/ImGui::GetIO().Framerate,ImGui::GetIO().Framerate);

    ImGui::End();

}

// feed inputs to dearIMGUI, start a new frame
void UseImGui::NewFrame(){
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UseImGui::Render(){
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UseImGui::Shutdown(){
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}