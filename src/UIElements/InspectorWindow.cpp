#include "InspectorWindow.h"

void InspectorWindow::Display(Object& SelectedObject)
{
	ImGui::Begin(Window::title.c_str());

	DisplayObjectInfo(SelectedObject);

	DisplayObjectPosition(SelectedObject);
	DisplayObjectOrientation(SelectedObject);
	DisplayObjectScale(SelectedObject);
	DisplayObjectColor(SelectedObject);

	DisplayObjectForcesCheckBox(SelectedObject);
	DisplayObjectVisibilityCheckBox(SelectedObject);

	ImGui::End();
}

void InspectorWindow::DisplayObjectInfo(Object& SelectedObject)
{
	ImGui::Text(formatObjectInfo(SelectedObject).c_str());
}

std::string InspectorWindow::formatObjectInfo(Object& SelectedObject)
{
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

	ObjectData += "Mass: " + std::to_string(SelectedObject.getRigidBody().getMass()) + " kg\n";

	return ObjectData;
}

void InspectorWindow::DisplayObjectPosition(Object& SelectedObject)
{
	glm::vec3 glmPosition = SelectedObject.getPosition();
	
	float position[3] = { 
		glmPosition.x, glmPosition.y, glmPosition.z 
	};

	if (ImGui::InputFloat3("Position", position))
	{
		SelectedObject.setPosition(glm::vec3(position[0], position[1], position[2]));
		SelectedObject.setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	}
}

void InspectorWindow::DisplayObjectOrientation(Object& SelectedObject)
{
	glm::vec3 glmOrientation = SelectedObject.getRigidBody().getOrientation();
	
	float orientation[3] = { 
		glmOrientation.x, glmOrientation.y, glmOrientation.z 
	};
	
	if (ImGui::InputFloat3("Orientation", orientation))
	{
		for (float& orientationAxis : orientation)
		{
			orientationAxis -= 360 * ((int)orientationAxis / 360);
		}

		SelectedObject.getRigidBody().changeOrientation(glm::vec3(orientation[0], orientation[1], orientation[2]));
	}
}

void InspectorWindow::DisplayObjectScale(Object& SelectedObject)
{
	glm::vec3 glmScale = SelectedObject.getRigidBody().getScale();
	
	float scale[3] = { 
		glmScale.x, glmScale.y, glmScale.z 
	};
	
	if (ImGui::InputFloat3("Scale", scale))
	{
		SelectedObject.getRigidBody().Rescale(glm::vec3(scale[0], scale[1], scale[2]));
	}
}

void InspectorWindow::DisplayObjectColor(Object& SelectedObject)
{
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
}

void InspectorWindow::DisplayObjectForcesCheckBox(Object& SelectedObject)
{
	ImGui::Checkbox("Is affected by forces", &SelectedObject.getRigidBody().isAffectedByForces);
}

void InspectorWindow::DisplayObjectVisibilityCheckBox(Object& SelectedObject)
{
	ImGui::Checkbox("Is visible", &SelectedObject.getGraphicsComponent().isVisible);
}
