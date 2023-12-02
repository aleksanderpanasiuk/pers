#include "ObjectListWindow.h"


void ObjectListWindow::Display(std::vector<Object>& Objects)
{
	ImGui::Begin(ObjectListWindow::title.c_str());

	for (Object& object : Objects)
	{
		ImGui::Button(std::to_string(object.getID()).c_str());
	}

	ImGui::End();
}