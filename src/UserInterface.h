#ifndef USER_INTERFACE_CLASS_H
#define USER_INTERFACE_CLASS_H

#include "Window.h"

class UserInterface
{
public:
	void init(GLFWwindow* window);
	void Display(float deltaTime, float FrameDelta, std::string InspectorData);
	void close();

private:
	Window DiagnosticWindow;
	Window InspectorWindow;
};

#endif // !USER_INTERFACE_CLASS_H
