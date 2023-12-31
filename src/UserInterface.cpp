#include "UserInterface.h"

void UserInterface::init(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	diagnosticWindow.setTitle("Diagnostics");
	inspectorWindow.setTitle("Inspector Window");
	HelpWindow.setTitle("Help");
	ObjectsList.setTitle("Objects");
}

void UserInterface::Display(
	float deltaTime, 
	float FrameDelta, 
	Object& SelectedObject,
	unsigned int& SelectedObjectID,
	std::vector<Object>& objectsList
)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// diagnostic window
	diagnosticWindow.Display(deltaTime, FrameDelta);

	// inspector window
	inspectorWindow.Display(SelectedObject);

	// help/controls window
	HelpWindow.setContent(controls);
	HelpWindow.Display();

	// Object list window
	ObjectsList.Display(SelectedObjectID, objectsList);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void UserInterface::close()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}