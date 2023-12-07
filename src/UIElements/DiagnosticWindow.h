#ifndef DIAGNOSTIC_WINDOW_CLASS_H
#define DIAGNOSTIC_WINDOW_CLASS_H

#include "Window.h"

class DiagnosticWindow : public Window
{
public:
	void Display(float deltaTime, float FrameDelta);

private:
	float deltaTimesamples[100] = { 0.0f };
};

#endif // !DIAGNOSTIC_WINDOW_CLASS_H
