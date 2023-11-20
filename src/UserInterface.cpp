#include "UserInterface.h"

void UserInterface::init(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void UserInterface::Display(float deltaTime, float FrameDelta)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	std::string diagnosticData =
		"Delta Time: " + std::to_string(deltaTime) + "\n" +
		"Frame Delta Time: " + std::to_string(FrameDelta) + "\n" +
		"Frames per second: " + std::to_string(1 / FrameDelta) + "\n";

	for (Window& window : windows)
	{
		window.setContent(diagnosticData);
		window.Display();
	}


	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::addWindow(std::string title, std::string content)
{
	int newId = windows.size();
	windows.push_back(Window(newId));
	windows[newId].setTitle(title);
	windows[newId].setContent(content);
}


void UserInterface::close()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}