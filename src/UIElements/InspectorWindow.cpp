#include "InspectorWindow.h"

void InspectorWindow::Display(Object& SelectedObject)
{
	ImGui::Begin(Window::title.c_str());

	std::string ObjectData = "Name: " + SelectedObject.getName() + "\n";

	ObjectData += "ID: " + std::to_string(SelectedObject.getID()) + "\n";

	ObjectData += "Object type: ";

	switch (SelectedObject.getType())
	{
	case RigidCube:
		ObjectData += "Cube\n";
		break;
	default:
		ObjectData += "Object\n";
		break;
	}

	ObjectData += "Position: \n";
	ObjectData += "\tx:" + std::to_string(SelectedObject.getPosition().x) + "\n";
	ObjectData += "\ty:" + std::to_string(SelectedObject.getPosition().y) + "\n";
	ObjectData += "\tz:" + std::to_string(SelectedObject.getPosition().z) + "\n";

	ImGui::Text(ObjectData.c_str());

	glm::vec3 glmColor = SelectedObject.getColor();

	float color[4] = {
		glmColor.x,
		glmColor.y,
		glmColor.z,
		0.0f,
	};

	if (ImGui::ColorEdit4("Color", color))
	{
		glm::vec3 newColor = glm::vec3(color[0], color[1], color[2]);
		SelectedObject.changeColor(newColor);
	}

	ImGui::End();
}