#include "ObjectListWindow.h"


void ObjectListWindow::Display(
	unsigned int& SelectedObjectID,
	std::vector<Object>& Objects
)
{
	ImGui::Begin(ObjectListWindow::title.c_str());

	for (Object& object : Objects)
	{
		if (ImGui::Button(object.getName().c_str()))
		{
			SelectedObjectID = object.getID();
		}
	}

	ImGui::End();
}