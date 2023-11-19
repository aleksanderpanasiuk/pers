#include "Inspector.h"


void Inspector::Update(std::vector<Object>& objects, Camera camera)
{
	glm::vec3 cameraNormal = camera.Orientation;
	glm::vec3 cameraPosition = camera.Position;

	for (Object& object : objects)
	{
		switch (object.getType())
		{
		case RigidCube:
			CheckHoverCube(object);
			break;
		default:
			break;
		}
	}
}

std::string Inspector::getSelectedObjectData()
{
	return std::string();
}

void Inspector::CheckHoverCube(Object& Cube)
{

}

glm::vec4 Inspector::calculatePlane()
{
	return glm::vec4();
}

glm::vec3 Inspector::calculatePoint()
{
	return glm::vec3();
}
