#include "UserInterface.h"

void UserInterface::init(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	DiagnosticWindow.setTitle("Diagnostics");
	InspectorWindow.setTitle("Inspector Window");
}

void UserInterface::Display(float deltaTime, float FrameDelta, std::string InspectorData)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// diagnostic window
	std::string diagnosticData =
		"Delta Time: " + std::to_string(deltaTime) + "\n" +
		"Frame Delta Time: " + std::to_string(FrameDelta) + "\n" +
		"Frames per second: " + std::to_string(1 / FrameDelta) + "\n";

	DiagnosticWindow.setContent(diagnosticData);
	DiagnosticWindow.Display();

	// inspector window
	InspectorWindow.setContent(InspectorData);
	InspectorWindow.Display();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void UserInterface::close()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}