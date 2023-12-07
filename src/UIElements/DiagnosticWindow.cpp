#include "DiagnosticWindow.h"

void DiagnosticWindow::Display(float deltaTime, float FrameDelta)
{
	ImGui::Begin(DiagnosticWindow::title.c_str());

	std::string diagnosticData =
		"Delta Time: " + std::to_string(deltaTime) + "\n" +
		"Frame Delta Time: " + std::to_string(FrameDelta) + "\n" +
		"Frames per second: " + std::to_string(1 / FrameDelta) + "\n";

	ImGui::Text(diagnosticData.c_str());

	UpdateQueue(deltaTime);

	std::queue<float> deltaTimesamplesCopy = deltaTimesamples;
	float deltaTimesamplesArray[numberOfSamples];
	int i = 0;

	while (not deltaTimesamplesCopy.empty())
	{
		deltaTimesamplesArray[i] = deltaTimesamplesCopy.front();
		deltaTimesamplesCopy.pop();
		i++;
	}

	ImGui::PlotLines("DeltaTime change", deltaTimesamplesArray, numberOfSamples);

	ImGui::End();
}

void DiagnosticWindow::UpdateQueue(float deltaTime)
{
	deltaTimesamples.push(deltaTime);

	if (deltaTimesamples.size() > numberOfSamples)
		deltaTimesamples.pop();
}
