#ifndef USER_INTERFACE_CLASS_H
#define USER_INTERFACE_CLASS_H

#include "Window.h"

class UserInterface
{
public:
	void init(GLFWwindow* window);
	void Display(float deltaTime, float FrameDelta);
	void close();
	void addWindow(std::string title, std::string content);

private:
	std::vector<Window> windows;
};

#endif // !USER_INTERFACE_CLASS_H
