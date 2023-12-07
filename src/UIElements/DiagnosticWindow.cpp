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

	ImGui::PlotLines("DeltaTime change", getDeltaTimeSamples().data(), numberOfSamples);

	ImGui::End();
}

void DiagnosticWindow::UpdateQueue(float deltaTime)
{
	deltaTimesamples.push(deltaTime);

	if (deltaTimesamples.size() > numberOfSamples)
		deltaTimesamples.pop();
}

std::vector<float> DiagnosticWindow::getDeltaTimeSamples()
{
	std::queue<float> deltaTimesamplesCopy = deltaTimesamples;
	std::vector<float> deltaTimesamplesArray;

	while (not deltaTimesamplesCopy.empty())
	{
		deltaTimesamplesArray.push_back(deltaTimesamplesCopy.front());
		deltaTimesamplesCopy.pop();
	}

	return deltaTimesamplesArray;
}
