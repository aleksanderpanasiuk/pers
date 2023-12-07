#ifndef DIAGNOSTIC_WINDOW_CLASS_H
#define DIAGNOSTIC_WINDOW_CLASS_H

#include <queue>

#include "Window.h"

class DiagnosticWindow : public Window
{
public:
	void Display(float deltaTime, float FrameDelta);

private:
	std::queue<float> deltaTimesamples;
	static const int numberOfSamples = 100;
};

#endif // !DIAGNOSTIC_WINDOW_CLASS_H
