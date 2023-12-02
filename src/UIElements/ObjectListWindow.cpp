#include "ObjectListWindow.h"


void ObjectListWindow::Display(
	unsigned int& SelectedobjectID,
	std::vector<Object>& Objects
)
{
	ImGui::Begin(ObjectListWindow::title.c_str());

	for (Object& object : Objects)
	{
		if (ImGui::Button(object.getName().c_str()))
		{
			SelectedobjectID = object.getID();
		}
	}

	ImGui::End();
}