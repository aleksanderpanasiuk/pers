#include "ObjectListWindow.h"


void ObjectListWindow::Display(
	unsigned int& Selectedobject,
	std::vector<Object>& Objects
)
{
	ImGui::Begin(ObjectListWindow::title.c_str());

	for (Object& object : Objects)
	{
		std::string NameDisplayed = object.getName();

		if (ImGui::Button(NameDisplayed.c_str()))
		{
			Selectedobject = object.getID();
		}
	}

	ImGui::End();
}