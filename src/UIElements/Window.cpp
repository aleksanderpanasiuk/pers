#include "Window.h"

void Window::setTitle(std::string title)
{
	Window::title = title;
}

std::string Window::getTitle()
{
	return Window::title;
}

void Window::setContent(std::string content)
{
	Window::content = content;
}

std::string Window::getContent()
{
	return Window::content;
}

void Window::Display()
{
	ImGui::Begin(Window::title.c_str());
	ImGui::Text(Window::content.c_str());

	ImGui::End();
}