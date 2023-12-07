#include "DiagnosticWindow.h"

void DiagnosticWindow::Display(float deltaTime, float FrameDelta)
{
	ImGui::Begin(DiagnosticWindow::title.c_str());

	std::string diagnosticData =
		"Delta Time: " + std::to_string(deltaTime) + "\n" +
		"Frame Delta Time: " + std::to_string(FrameDelta) + "\n" +
		"Frames per second: " + std::to_string(1 / FrameDelta) + "\n";

	ImGui::Text(diagnosticData.c_str());

	ImGui::End();
}
