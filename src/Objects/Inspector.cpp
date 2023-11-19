#include "Inspector.h"


void Inspector::Update(std::vector<Object>& objects, Camera camera)
{
	glm::vec3 cameraNormal = camera.Orientation;
	glm::vec3 cameraPosition = camera.Position;

	for (Object& object : objects)
	{
		bool isPointing = false;

		switch (object.getType())
		{
		case RigidCube:
			isPointing = CheckHoverCube(object, cameraPosition, cameraNormal);
			break;
		default:
			break;
		}

		if (isPointing)
		{
			SelectedObject = std::make_unique<Object>(object);
			break;
		}
	}
}

std::string Inspector::getSelectedObjectData()
{
	return std::string();
}

bool Inspector::CheckHoverCube(Object& Cube, glm::vec3 cameraPosition, glm::vec3 cameraNormal)
{
	std::vector<std::vector<glm::vec3>> Sides = Cube.getSides();

	for (std::vector<glm::vec3> side : Sides)
	{
		bool check = CheckHoverPlane(side, cameraPosition, cameraNormal);
		if (check)
			return true;
	}

	return false;
}

bool Inspector::CheckHoverPlane(std::vector<glm::vec3> Side, glm::vec3 cameraPosition, glm::vec3 cameraNormal)
{
	glm::vec4 Plane = calculatePlane(Side);
	glm::vec3 Point = calculatePoint(Plane, cameraPosition, cameraNormal);

	return false;
}

glm::vec4 Inspector::calculatePlane(std::vector<glm::vec3> Side)
{
	glm::vec3 S1 = Side[0];
	glm::vec3 S2 = Side[1];
	glm::vec3 S3 = Side[2];

	float A = (S2.y - S1.y) * (S3.z - S1.z) - (S2.z - S1.z) * (S3.y - S1.y);
	float B = (S2.z - S1.z) * (S3.x - S1.x) - (S2.x - S1.x) * (S3.z - S1.z);
	float C = (S2.x - S1.x) * (S3.y - S1.y) - (S2.y - S1.y) * (S3.x - S1.x);
	float D = -(A * S1.x + B * S1.y + C * S1.z);

	return glm::vec4(A, B, C, D);
}

glm::vec3 Inspector::calculatePoint(glm::vec4 Plane, glm::vec3 cameraPosition, glm::vec3 cameraNormal)
{
	float t = (-Plane.x * cameraPosition.x - Plane.y * cameraPosition.y - Plane.z * cameraPosition.z - Plane.w) /
		(Plane.x * cameraNormal.x + Plane.y * cameraNormal.y + Plane.z * cameraNormal.z);

	return glm::vec3(
		cameraPosition[0] + t * cameraNormal[0],
		cameraPosition[1] + t * cameraNormal[1],
		cameraPosition[2] + t * cameraNormal[2]
	);
}
