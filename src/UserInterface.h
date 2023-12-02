#ifndef USER_INTERFACE_CLASS_H
#define USER_INTERFACE_CLASS_H

#include "Window.h"
#include "Objects/Object.h"

class UserInterface
{
public:
	void init(GLFWwindow* window);
	void Display(
		float deltaTime, 
		float FrameDelta, 
		std::string InspectorData,
		std::vector<Object> &objectsList
	);

	void close();

private:
	Window DiagnosticWindow;
	Window InspectorWindow;
	Window HelpWindow;
	Window ObjectsList;

	std::string controls = "WASD - camera movement\n"
		"Shift - Down\n"
		"Space - Up\n"
		"RMB+Mouse - camera rotation\n"
		"LCTRL+LMB - spawn cube\n";
};

#endif // !USER_INTERFACE_CLASS_H
