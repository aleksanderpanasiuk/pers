#ifndef USER_INTERFACE_CLASS_H
#define USER_INTERFACE_CLASS_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class UserInterface
{
public:
	void init(GLFWwindow* window);
	void display();
};

#endif // !USER_INTERFACE_CLASS_H
