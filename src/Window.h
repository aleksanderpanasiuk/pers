#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <String>
#include <Vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Window
{
public:
	Window(unsigned int ID);

	void setTitle(std::string title);
	std::string getTitle();
	void setContent(std::string content);
	std::string getContent();
	void Display();

private:
	unsigned int ID;
	std::string title = "";
	std::string content = "";
};

#endif // !WINDOW_CLASS_H
