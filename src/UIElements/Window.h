#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <String>
#include <Vector>

#include "../Objects/Object.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Window
{
public:
	void setTitle(std::string title);
	std::string getTitle();
	void setContent(std::string content);
	std::string getContent();
	virtual void Display();

protected:
	std::string title = "";
	std::string content = "";
};

#endif // !WINDOW_CLASS_H
