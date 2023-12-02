#ifndef USER_INTERFACE_CLASS_H
#define USER_INTERFACE_CLASS_H

#include "UIElements/Window.h"
#include "UIElements/ObjectListWindow.h"
#include "Objects/Object.h"

class UserInterface
{
public:
	void init(GLFWwindow* window);
	void Display(
		float deltaTime, 
		float FrameDelta, 
		std::string InspectorData,
		unsigned int &Selectedobject,
		std::vector<Object> &objectsList
	);

	void close();

private:
	Window DiagnosticWindow;
	Window InspectorWindow;
	Window HelpWindow;
	ObjectListWindow ObjectsList;

	std::string controls = "WASD - camera movement\n"
		"Shift - Down\n"
		"Space - Up\n"
		"RMB+Mouse - camera rotation\n"
		"LCTRL+LMB - spawn cube\n";
};

#endif // !USER_INTERFACE_CLASS_H
